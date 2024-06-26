/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/index/bplus_tree_index.h"
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept { close(); }

RC BplusTreeIndex::create(
    const char *file_name, const IndexMeta &index_meta, std::vector<const FieldMeta *> &field_metas, bool is_unique)
{
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s, field:%s",
        file_name,
        index_meta.name(),
        index_meta.field_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas, is_unique);

  // 设置类型,
  // 如果是多个字段 -> 设置为MULTI
  // 如果只有一个字段 -> 设置为第一个字段的类型
  std::vector<AttrType> attr_types;
  for (auto &field_meta : field_metas) {
    attr_types.push_back(field_meta->type());
  }

  // 计算联合索引的长度
  std::vector<int32_t> attr_lens;
  for (int i = 0; i < field_metas.size(); i++) {
    attr_lens.push_back(field_metas[i]->len());
  }

  RC rc = index_handler_.create(file_name, attr_types, attr_lens, is_unique);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name,
        index_meta.name(),
        index_meta.field_str(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully create index, file_name:%s, index:%s, field:%s", file_name, index_meta.name(), index_meta.field_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, std::vector<const FieldMeta *> &field_metas)
{
  if (inited_) {
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index:%s, field:%s",
        file_name,
        index_meta.name(),
        index_meta.field_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas, index_meta.is_unique());

  RC rc = index_handler_.open(file_name, field_metas);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to open index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name,
        index_meta.name(),
        index_meta.field_str(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully open index, file_name:%s, index:%s, field:%s", file_name, index_meta.name(), index_meta.field_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::close()
{
  if (inited_) {
    LOG_INFO("Begin to close index, index:%s, field:%s", index_meta_.name(), index_meta_.field_str());
    index_handler_.close();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}

RC BplusTreeIndex::drop()
{
  RC rc = RC::SUCCESS;
  if (inited_) {
    LOG_INFO("Begin to drop index, index:%s, field:%s", index_meta_.name(), index_meta_.field_str());
    rc      = index_handler_.drop();
    inited_ = false;
  }
  LOG_INFO("Successfully drop index.");
  return rc;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid)
{
  RC rc = RC::SUCCESS;

  int offset = 0;
  for (const auto &field_meta : field_metas_) {
    offset += field_meta.len();
  }
  char idx_key[offset];
  memset(idx_key, 0, offset);
  for (const auto &field_meta : field_metas_) {
    memmove(idx_key, record + field_meta.offset(), field_meta.len());
  }

  if (is_unique_) {
    // 检查是否存在
    std::list<RID> res;
    rc = index_handler_.get_entry(idx_key, offset, res);
    if (rc != RC::RECORD_EOF && !res.empty())
      return RC::RECORD_INVALID_KEY;
  }
  rc = index_handler_.insert_entry(idx_key, offset, rid);
  return rc;
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  RC rc = RC::SUCCESS;

  int offset = 0;
  for (const auto &field_meta : field_metas_) {
    offset += field_meta.len();
  }
  char idx_key[offset];
  memset(idx_key, 0, offset);
  for (const auto &field_meta : field_metas_) {
    memmove(idx_key, record + field_meta.offset(), field_meta.len());
  }

  rc = index_handler_.delete_entry(idx_key, offset, rid);
  return rc;
}

IndexScanner *BplusTreeIndex::create_scanner(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(index_handler_);
  RC rc = index_scanner->open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete index_scanner;
    return nullptr;
  }
  return index_scanner;
}

RC BplusTreeIndex::sync() { return index_handler_.sync(); }

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeHandler &tree_handler) : tree_scanner_(tree_handler) {}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept { tree_scanner_.close(); }

RC BplusTreeIndexScanner::open(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  return tree_scanner_.open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

RC BplusTreeIndexScanner::next_entry(RID *rid) { return tree_scanner_.next_entry(*rid); }

RC BplusTreeIndexScanner::destroy()
{
  delete this;
  return RC::SUCCESS;
}
