// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocol.proto

#include "Protocol.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace Protocol {
PROTOBUF_CONSTEXPR C_LOGIN::C_LOGIN(
    ::_pbi::ConstantInitialized) {}
struct C_LOGINDefaultTypeInternal {
  PROTOBUF_CONSTEXPR C_LOGINDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~C_LOGINDefaultTypeInternal() {}
  union {
    C_LOGIN _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 C_LOGINDefaultTypeInternal _C_LOGIN_default_instance_;
PROTOBUF_CONSTEXPR S_LOGIN::S_LOGIN(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.players_)*/{}
  , /*decltype(_impl_._players_cached_byte_size_)*/{0}
  , /*decltype(_impl_.success_)*/false
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct S_LOGINDefaultTypeInternal {
  PROTOBUF_CONSTEXPR S_LOGINDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~S_LOGINDefaultTypeInternal() {}
  union {
    S_LOGIN _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 S_LOGINDefaultTypeInternal _S_LOGIN_default_instance_;
PROTOBUF_CONSTEXPR C_CHAT::C_CHAT(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.nickname_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.msg_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct C_CHATDefaultTypeInternal {
  PROTOBUF_CONSTEXPR C_CHATDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~C_CHATDefaultTypeInternal() {}
  union {
    C_CHAT _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 C_CHATDefaultTypeInternal _C_CHAT_default_instance_;
PROTOBUF_CONSTEXPR S_CHAT::S_CHAT(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.nickname_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.msg_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.playerid_)*/uint64_t{0u}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct S_CHATDefaultTypeInternal {
  PROTOBUF_CONSTEXPR S_CHATDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~S_CHATDefaultTypeInternal() {}
  union {
    S_CHAT _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 S_CHATDefaultTypeInternal _S_CHAT_default_instance_;
}  // namespace Protocol
static ::_pb::Metadata file_level_metadata_Protocol_2eproto[4];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_Protocol_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Protocol_2eproto = nullptr;

const uint32_t TableStruct_Protocol_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::C_LOGIN, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_LOGIN, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_LOGIN, _impl_.success_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_LOGIN, _impl_.players_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::C_CHAT, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::C_CHAT, _impl_.nickname_),
  PROTOBUF_FIELD_OFFSET(::Protocol::C_CHAT, _impl_.msg_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CHAT, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CHAT, _impl_.playerid_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CHAT, _impl_.nickname_),
  PROTOBUF_FIELD_OFFSET(::Protocol::S_CHAT, _impl_.msg_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Protocol::C_LOGIN)},
  { 6, -1, -1, sizeof(::Protocol::S_LOGIN)},
  { 14, -1, -1, sizeof(::Protocol::C_CHAT)},
  { 22, -1, -1, sizeof(::Protocol::S_CHAT)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Protocol::_C_LOGIN_default_instance_._instance,
  &::Protocol::_S_LOGIN_default_instance_._instance,
  &::Protocol::_C_CHAT_default_instance_._instance,
  &::Protocol::_S_CHAT_default_instance_._instance,
};

const char descriptor_table_protodef_Protocol_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016Protocol.proto\022\010Protocol\"\t\n\007C_LOGIN\"+\n"
  "\007S_LOGIN\022\017\n\007success\030\001 \001(\010\022\017\n\007players\030\002 \003"
  "(\005\"\'\n\006C_CHAT\022\020\n\010nickname\030\001 \001(\t\022\013\n\003msg\030\002 "
  "\001(\t\"9\n\006S_CHAT\022\020\n\010playerId\030\001 \001(\004\022\020\n\010nickn"
  "ame\030\002 \001(\t\022\013\n\003msg\030\003 \001(\tb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_Protocol_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Protocol_2eproto = {
    false, false, 190, descriptor_table_protodef_Protocol_2eproto,
    "Protocol.proto",
    &descriptor_table_Protocol_2eproto_once, nullptr, 0, 4,
    schemas, file_default_instances, TableStruct_Protocol_2eproto::offsets,
    file_level_metadata_Protocol_2eproto, file_level_enum_descriptors_Protocol_2eproto,
    file_level_service_descriptors_Protocol_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Protocol_2eproto_getter() {
  return &descriptor_table_Protocol_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Protocol_2eproto(&descriptor_table_Protocol_2eproto);
namespace Protocol {

// ===================================================================

class C_LOGIN::_Internal {
 public:
};

C_LOGIN::C_LOGIN(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase(arena, is_message_owned) {
  // @@protoc_insertion_point(arena_constructor:Protocol.C_LOGIN)
}
C_LOGIN::C_LOGIN(const C_LOGIN& from)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase() {
  C_LOGIN* const _this = this; (void)_this;
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Protocol.C_LOGIN)
}





const ::PROTOBUF_NAMESPACE_ID::Message::ClassData C_LOGIN::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl,
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl,
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*C_LOGIN::GetClassData() const { return &_class_data_; }







::PROTOBUF_NAMESPACE_ID::Metadata C_LOGIN::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Protocol_2eproto_getter, &descriptor_table_Protocol_2eproto_once,
      file_level_metadata_Protocol_2eproto[0]);
}

// ===================================================================

class S_LOGIN::_Internal {
 public:
};

S_LOGIN::S_LOGIN(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Protocol.S_LOGIN)
}
S_LOGIN::S_LOGIN(const S_LOGIN& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  S_LOGIN* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.players_){from._impl_.players_}
    , /*decltype(_impl_._players_cached_byte_size_)*/{0}
    , decltype(_impl_.success_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.success_ = from._impl_.success_;
  // @@protoc_insertion_point(copy_constructor:Protocol.S_LOGIN)
}

inline void S_LOGIN::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.players_){arena}
    , /*decltype(_impl_._players_cached_byte_size_)*/{0}
    , decltype(_impl_.success_){false}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

S_LOGIN::~S_LOGIN() {
  // @@protoc_insertion_point(destructor:Protocol.S_LOGIN)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void S_LOGIN::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.players_.~RepeatedField();
}

void S_LOGIN::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void S_LOGIN::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.S_LOGIN)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.players_.Clear();
  _impl_.success_ = false;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* S_LOGIN::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bool success = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.success_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 players = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_players(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 16) {
          _internal_add_players(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* S_LOGIN::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.S_LOGIN)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bool success = 1;
  if (this->_internal_success() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(1, this->_internal_success(), target);
  }

  // repeated int32 players = 2;
  {
    int byte_size = _impl_._players_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          2, _internal_players(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.S_LOGIN)
  return target;
}

size_t S_LOGIN::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.S_LOGIN)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 players = 2;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int32Size(this->_impl_.players_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _impl_._players_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // bool success = 1;
  if (this->_internal_success() != 0) {
    total_size += 1 + 1;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData S_LOGIN::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    S_LOGIN::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*S_LOGIN::GetClassData() const { return &_class_data_; }


void S_LOGIN::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<S_LOGIN*>(&to_msg);
  auto& from = static_cast<const S_LOGIN&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Protocol.S_LOGIN)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.players_.MergeFrom(from._impl_.players_);
  if (from._internal_success() != 0) {
    _this->_internal_set_success(from._internal_success());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void S_LOGIN::CopyFrom(const S_LOGIN& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.S_LOGIN)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S_LOGIN::IsInitialized() const {
  return true;
}

void S_LOGIN::InternalSwap(S_LOGIN* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.players_.InternalSwap(&other->_impl_.players_);
  swap(_impl_.success_, other->_impl_.success_);
}

::PROTOBUF_NAMESPACE_ID::Metadata S_LOGIN::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Protocol_2eproto_getter, &descriptor_table_Protocol_2eproto_once,
      file_level_metadata_Protocol_2eproto[1]);
}

// ===================================================================

class C_CHAT::_Internal {
 public:
};

C_CHAT::C_CHAT(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Protocol.C_CHAT)
}
C_CHAT::C_CHAT(const C_CHAT& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  C_CHAT* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.nickname_){}
    , decltype(_impl_.msg_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.nickname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.nickname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_nickname().empty()) {
    _this->_impl_.nickname_.Set(from._internal_nickname(), 
      _this->GetArenaForAllocation());
  }
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_msg().empty()) {
    _this->_impl_.msg_.Set(from._internal_msg(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:Protocol.C_CHAT)
}

inline void C_CHAT::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.nickname_){}
    , decltype(_impl_.msg_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.nickname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.nickname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

C_CHAT::~C_CHAT() {
  // @@protoc_insertion_point(destructor:Protocol.C_CHAT)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void C_CHAT::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.nickname_.Destroy();
  _impl_.msg_.Destroy();
}

void C_CHAT::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void C_CHAT::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.C_CHAT)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.nickname_.ClearToEmpty();
  _impl_.msg_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* C_CHAT::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string nickname = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_nickname();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Protocol.C_CHAT.nickname"));
        } else
          goto handle_unusual;
        continue;
      // string msg = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_msg();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Protocol.C_CHAT.msg"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* C_CHAT::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.C_CHAT)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string nickname = 1;
  if (!this->_internal_nickname().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_nickname().data(), static_cast<int>(this->_internal_nickname().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.C_CHAT.nickname");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_nickname(), target);
  }

  // string msg = 2;
  if (!this->_internal_msg().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_msg().data(), static_cast<int>(this->_internal_msg().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.C_CHAT.msg");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_msg(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.C_CHAT)
  return target;
}

size_t C_CHAT::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.C_CHAT)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string nickname = 1;
  if (!this->_internal_nickname().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_nickname());
  }

  // string msg = 2;
  if (!this->_internal_msg().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_msg());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData C_CHAT::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    C_CHAT::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*C_CHAT::GetClassData() const { return &_class_data_; }


void C_CHAT::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<C_CHAT*>(&to_msg);
  auto& from = static_cast<const C_CHAT&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Protocol.C_CHAT)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_nickname().empty()) {
    _this->_internal_set_nickname(from._internal_nickname());
  }
  if (!from._internal_msg().empty()) {
    _this->_internal_set_msg(from._internal_msg());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void C_CHAT::CopyFrom(const C_CHAT& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.C_CHAT)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool C_CHAT::IsInitialized() const {
  return true;
}

void C_CHAT::InternalSwap(C_CHAT* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.nickname_, lhs_arena,
      &other->_impl_.nickname_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.msg_, lhs_arena,
      &other->_impl_.msg_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata C_CHAT::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Protocol_2eproto_getter, &descriptor_table_Protocol_2eproto_once,
      file_level_metadata_Protocol_2eproto[2]);
}

// ===================================================================

class S_CHAT::_Internal {
 public:
};

S_CHAT::S_CHAT(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Protocol.S_CHAT)
}
S_CHAT::S_CHAT(const S_CHAT& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  S_CHAT* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.nickname_){}
    , decltype(_impl_.msg_){}
    , decltype(_impl_.playerid_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.nickname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.nickname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_nickname().empty()) {
    _this->_impl_.nickname_.Set(from._internal_nickname(), 
      _this->GetArenaForAllocation());
  }
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_msg().empty()) {
    _this->_impl_.msg_.Set(from._internal_msg(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.playerid_ = from._impl_.playerid_;
  // @@protoc_insertion_point(copy_constructor:Protocol.S_CHAT)
}

inline void S_CHAT::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.nickname_){}
    , decltype(_impl_.msg_){}
    , decltype(_impl_.playerid_){uint64_t{0u}}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.nickname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.nickname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

S_CHAT::~S_CHAT() {
  // @@protoc_insertion_point(destructor:Protocol.S_CHAT)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void S_CHAT::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.nickname_.Destroy();
  _impl_.msg_.Destroy();
}

void S_CHAT::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void S_CHAT::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.S_CHAT)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.nickname_.ClearToEmpty();
  _impl_.msg_.ClearToEmpty();
  _impl_.playerid_ = uint64_t{0u};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* S_CHAT::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 playerId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.playerid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string nickname = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_nickname();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Protocol.S_CHAT.nickname"));
        } else
          goto handle_unusual;
        continue;
      // string msg = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_msg();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Protocol.S_CHAT.msg"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* S_CHAT::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.S_CHAT)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 playerId = 1;
  if (this->_internal_playerid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_playerid(), target);
  }

  // string nickname = 2;
  if (!this->_internal_nickname().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_nickname().data(), static_cast<int>(this->_internal_nickname().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.S_CHAT.nickname");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_nickname(), target);
  }

  // string msg = 3;
  if (!this->_internal_msg().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_msg().data(), static_cast<int>(this->_internal_msg().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Protocol.S_CHAT.msg");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_msg(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.S_CHAT)
  return target;
}

size_t S_CHAT::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.S_CHAT)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string nickname = 2;
  if (!this->_internal_nickname().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_nickname());
  }

  // string msg = 3;
  if (!this->_internal_msg().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_msg());
  }

  // uint64 playerId = 1;
  if (this->_internal_playerid() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_playerid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData S_CHAT::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    S_CHAT::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*S_CHAT::GetClassData() const { return &_class_data_; }


void S_CHAT::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<S_CHAT*>(&to_msg);
  auto& from = static_cast<const S_CHAT&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Protocol.S_CHAT)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_nickname().empty()) {
    _this->_internal_set_nickname(from._internal_nickname());
  }
  if (!from._internal_msg().empty()) {
    _this->_internal_set_msg(from._internal_msg());
  }
  if (from._internal_playerid() != 0) {
    _this->_internal_set_playerid(from._internal_playerid());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void S_CHAT::CopyFrom(const S_CHAT& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.S_CHAT)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S_CHAT::IsInitialized() const {
  return true;
}

void S_CHAT::InternalSwap(S_CHAT* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.nickname_, lhs_arena,
      &other->_impl_.nickname_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.msg_, lhs_arena,
      &other->_impl_.msg_, rhs_arena
  );
  swap(_impl_.playerid_, other->_impl_.playerid_);
}

::PROTOBUF_NAMESPACE_ID::Metadata S_CHAT::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Protocol_2eproto_getter, &descriptor_table_Protocol_2eproto_once,
      file_level_metadata_Protocol_2eproto[3]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::C_LOGIN*
Arena::CreateMaybeMessage< ::Protocol::C_LOGIN >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::C_LOGIN >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::S_LOGIN*
Arena::CreateMaybeMessage< ::Protocol::S_LOGIN >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::S_LOGIN >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::C_CHAT*
Arena::CreateMaybeMessage< ::Protocol::C_CHAT >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::C_CHAT >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::S_CHAT*
Arena::CreateMaybeMessage< ::Protocol::S_CHAT >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::S_CHAT >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
