#pragma once
#include <eos/types/types.hpp>

namespace eos { namespace types {

using std::map;
using std::string;
using std::function;
using std::pair;

/**
 *  Describes the binary representation message and table contents so that it can
 *  be converted to and from JSON.
 */
struct AbiSerializer {
   AbiSerializer(){ configureTypes(); }
   AbiSerializer( const Abi& abi );
   void setAbi( const Abi& abi );

   map<TypeName, TypeName> typedefs;
   map<TypeName, Struct>   structs;
   map<Name,TypeName>      actions;
   map<Name,TypeName>      tables;

   typedef std::function<fc::variant(fc::datastream<const char*>&)>  pack_function;
   typedef std::function<void(const fc::variant&, fc::datastream<char*>&)>  unpack_function;
   
   map<TypeName, pair<pack_function, unpack_function>> native_types;
   void configureTypes();

   void validate()const;

   TypeName resolveType( const TypeName& t )const;
   bool isType( const TypeName& type )const;
   bool isStruct( const TypeName& type )const;

   const Struct& getStruct( const TypeName& type )const;

   TypeName getActionType( Name action )const;
   TypeName getTableType( Name action )const;

   fc::variant binaryToVariant(const TypeName& type, const Bytes& binary)const;
   Bytes       variantToBinary(const TypeName& type, const fc::variant& var)const;

   fc::variant binaryToVariant(const TypeName& type, fc::datastream<const char*>& binary )const;
   void        variantToBinary(const TypeName& type, const fc::variant& var, fc::datastream<char*>& ds )const;

   private:
   void binaryToVariant(const TypeName& type, fc::datastream<const char*>& stream, fc::mutable_variant_object& obj )const;
};

} } // eos::types
