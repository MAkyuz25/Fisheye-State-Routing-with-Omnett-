//
// Generated file, do not edit! Created by opp_msgtool 6.1 from inet/routing/fsr/FsrPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "FsrPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

LinkStateEntry::LinkStateEntry()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const LinkStateEntry& a)
{
    doParsimPacking(b,a.destAddress);
    doParsimPacking(b,a.sequenceNumber);
    doParsimPacking(b,a.neighborsStartIndex);
    doParsimPacking(b,a.neighborsSize);
}

void __doUnpacking(omnetpp::cCommBuffer *b, LinkStateEntry& a)
{
    doParsimUnpacking(b,a.destAddress);
    doParsimUnpacking(b,a.sequenceNumber);
    doParsimUnpacking(b,a.neighborsStartIndex);
    doParsimUnpacking(b,a.neighborsSize);
}

class LinkStateEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destAddress,
        FIELD_sequenceNumber,
        FIELD_neighborsStartIndex,
        FIELD_neighborsSize,
    };
  public:
    LinkStateEntryDescriptor();
    virtual ~LinkStateEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LinkStateEntryDescriptor)

LinkStateEntryDescriptor::LinkStateEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LinkStateEntry)), "")
{
    propertyNames = nullptr;
}

LinkStateEntryDescriptor::~LinkStateEntryDescriptor()
{
    delete[] propertyNames;
}

bool LinkStateEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinkStateEntry *>(obj)!=nullptr;
}

const char **LinkStateEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LinkStateEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LinkStateEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int LinkStateEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_destAddress
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_neighborsStartIndex
        FD_ISEDITABLE,    // FIELD_neighborsSize
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *LinkStateEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destAddress",
        "sequenceNumber",
        "neighborsStartIndex",
        "neighborsSize",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int LinkStateEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "neighborsStartIndex") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "neighborsSize") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *LinkStateEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_destAddress
        "uint32",    // FIELD_sequenceNumber
        "uint8",    // FIELD_neighborsStartIndex
        "uint8",    // FIELD_neighborsSize
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **LinkStateEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LinkStateEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LinkStateEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LinkStateEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LinkStateEntry'", field);
    }
}

const char *LinkStateEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinkStateEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destAddress: return pp->destAddress.str();
        case FIELD_sequenceNumber: return ulong2string(pp->sequenceNumber);
        case FIELD_neighborsStartIndex: return ulong2string(pp->neighborsStartIndex);
        case FIELD_neighborsSize: return ulong2string(pp->neighborsSize);
        default: return "";
    }
}

void LinkStateEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->sequenceNumber = string2ulong(value); break;
        case FIELD_neighborsStartIndex: pp->neighborsStartIndex = string2ulong(value); break;
        case FIELD_neighborsSize: pp->neighborsSize = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateEntry'", field);
    }
}

omnetpp::cValue LinkStateEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->destAddress); break;
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->sequenceNumber);
        case FIELD_neighborsStartIndex: return (omnetpp::intval_t)(pp->neighborsStartIndex);
        case FIELD_neighborsSize: return (omnetpp::intval_t)(pp->neighborsSize);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LinkStateEntry' as cValue -- field index out of range?", field);
    }
}

void LinkStateEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->sequenceNumber = omnetpp::checked_int_cast<uint32_t>(value.intValue()); break;
        case FIELD_neighborsStartIndex: pp->neighborsStartIndex = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        case FIELD_neighborsSize: pp->neighborsSize = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateEntry'", field);
    }
}

const char *LinkStateEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LinkStateEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->destAddress); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LinkStateEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateEntry *pp = omnetpp::fromAnyPtr<LinkStateEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateEntry'", field);
    }
}

Register_Class(FsrPacket)

FsrPacket::FsrPacket() : ::inet::FieldsChunk()
{
}

FsrPacket::FsrPacket(const FsrPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

FsrPacket::~FsrPacket()
{
    delete [] this->links;
    delete [] this->neighborsList;
}

FsrPacket& FsrPacket::operator=(const FsrPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void FsrPacket::copy(const FsrPacket& other)
{
    delete [] this->links;
    this->links = (other.links_arraysize==0) ? nullptr : new LinkStateEntry[other.links_arraysize];
    links_arraysize = other.links_arraysize;
    for (size_t i = 0; i < links_arraysize; i++) {
        this->links[i] = other.links[i];
    }
    delete [] this->neighborsList;
    this->neighborsList = (other.neighborsList_arraysize==0) ? nullptr : new Ipv4Address[other.neighborsList_arraysize];
    neighborsList_arraysize = other.neighborsList_arraysize;
    for (size_t i = 0; i < neighborsList_arraysize; i++) {
        this->neighborsList[i] = other.neighborsList[i];
    }
}

void FsrPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    b->pack(links_arraysize);
    doParsimArrayPacking(b,this->links,links_arraysize);
    b->pack(neighborsList_arraysize);
    doParsimArrayPacking(b,this->neighborsList,neighborsList_arraysize);
}

void FsrPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    delete [] this->links;
    b->unpack(links_arraysize);
    if (links_arraysize == 0) {
        this->links = nullptr;
    } else {
        this->links = new LinkStateEntry[links_arraysize];
        doParsimArrayUnpacking(b,this->links,links_arraysize);
    }
    delete [] this->neighborsList;
    b->unpack(neighborsList_arraysize);
    if (neighborsList_arraysize == 0) {
        this->neighborsList = nullptr;
    } else {
        this->neighborsList = new Ipv4Address[neighborsList_arraysize];
        doParsimArrayUnpacking(b,this->neighborsList,neighborsList_arraysize);
    }
}

size_t FsrPacket::getLinksArraySize() const
{
    return links_arraysize;
}

const LinkStateEntry& FsrPacket::getLinks(size_t k) const
{
    if (k >= links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    return this->links[k];
}

void FsrPacket::setLinksArraySize(size_t newSize)
{
    handleChange();
    LinkStateEntry *links2 = (newSize==0) ? nullptr : new LinkStateEntry[newSize];
    size_t minSize = links_arraysize < newSize ? links_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        links2[i] = this->links[i];
    delete [] this->links;
    this->links = links2;
    links_arraysize = newSize;
}

void FsrPacket::setLinks(size_t k, const LinkStateEntry& links)
{
    if (k >= links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    handleChange();
    this->links[k] = links;
}

void FsrPacket::insertLinks(size_t k, const LinkStateEntry& links)
{
    if (k > links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = links_arraysize + 1;
    LinkStateEntry *links2 = new LinkStateEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        links2[i] = this->links[i];
    links2[k] = links;
    for (i = k + 1; i < newSize; i++)
        links2[i] = this->links[i-1];
    delete [] this->links;
    this->links = links2;
    links_arraysize = newSize;
}

void FsrPacket::appendLinks(const LinkStateEntry& links)
{
    insertLinks(links_arraysize, links);
}

void FsrPacket::eraseLinks(size_t k)
{
    if (k >= links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = links_arraysize - 1;
    LinkStateEntry *links2 = (newSize == 0) ? nullptr : new LinkStateEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        links2[i] = this->links[i];
    for (i = k; i < newSize; i++)
        links2[i] = this->links[i+1];
    delete [] this->links;
    this->links = links2;
    links_arraysize = newSize;
}

size_t FsrPacket::getNeighborsListArraySize() const
{
    return neighborsList_arraysize;
}

const Ipv4Address& FsrPacket::getNeighborsList(size_t k) const
{
    if (k >= neighborsList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborsList_arraysize, (unsigned long)k);
    return this->neighborsList[k];
}

void FsrPacket::setNeighborsListArraySize(size_t newSize)
{
    handleChange();
    Ipv4Address *neighborsList2 = (newSize==0) ? nullptr : new Ipv4Address[newSize];
    size_t minSize = neighborsList_arraysize < newSize ? neighborsList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        neighborsList2[i] = this->neighborsList[i];
    delete [] this->neighborsList;
    this->neighborsList = neighborsList2;
    neighborsList_arraysize = newSize;
}

void FsrPacket::setNeighborsList(size_t k, const Ipv4Address& neighborsList)
{
    if (k >= neighborsList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborsList_arraysize, (unsigned long)k);
    handleChange();
    this->neighborsList[k] = neighborsList;
}

void FsrPacket::insertNeighborsList(size_t k, const Ipv4Address& neighborsList)
{
    if (k > neighborsList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborsList_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighborsList_arraysize + 1;
    Ipv4Address *neighborsList2 = new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborsList2[i] = this->neighborsList[i];
    neighborsList2[k] = neighborsList;
    for (i = k + 1; i < newSize; i++)
        neighborsList2[i] = this->neighborsList[i-1];
    delete [] this->neighborsList;
    this->neighborsList = neighborsList2;
    neighborsList_arraysize = newSize;
}

void FsrPacket::appendNeighborsList(const Ipv4Address& neighborsList)
{
    insertNeighborsList(neighborsList_arraysize, neighborsList);
}

void FsrPacket::eraseNeighborsList(size_t k)
{
    if (k >= neighborsList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborsList_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighborsList_arraysize - 1;
    Ipv4Address *neighborsList2 = (newSize == 0) ? nullptr : new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborsList2[i] = this->neighborsList[i];
    for (i = k; i < newSize; i++)
        neighborsList2[i] = this->neighborsList[i+1];
    delete [] this->neighborsList;
    this->neighborsList = neighborsList2;
    neighborsList_arraysize = newSize;
}

class FsrPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_links,
        FIELD_neighborsList,
    };
  public:
    FsrPacketDescriptor();
    virtual ~FsrPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(FsrPacketDescriptor)

FsrPacketDescriptor::FsrPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FsrPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

FsrPacketDescriptor::~FsrPacketDescriptor()
{
    delete[] propertyNames;
}

bool FsrPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FsrPacket *>(obj)!=nullptr;
}

const char **FsrPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FsrPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FsrPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int FsrPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_links
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_neighborsList
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *FsrPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "links",
        "neighborsList",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int FsrPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "links") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "neighborsList") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *FsrPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::LinkStateEntry",    // FIELD_links
        "inet::Ipv4Address",    // FIELD_neighborsList
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **FsrPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FsrPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FsrPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_links: return pp->getLinksArraySize();
        case FIELD_neighborsList: return pp->getNeighborsListArraySize();
        default: return 0;
    }
}

void FsrPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_links: pp->setLinksArraySize(size); break;
        case FIELD_neighborsList: pp->setNeighborsListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FsrPacket'", field);
    }
}

const char *FsrPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FsrPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_links: return "";
        case FIELD_neighborsList: return pp->getNeighborsList(i).str();
        default: return "";
    }
}

void FsrPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FsrPacket'", field);
    }
}

omnetpp::cValue FsrPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_links: return omnetpp::toAnyPtr(&pp->getLinks(i)); break;
        case FIELD_neighborsList: return omnetpp::toAnyPtr(&pp->getNeighborsList(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FsrPacket' as cValue -- field index out of range?", field);
    }
}

void FsrPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FsrPacket'", field);
    }
}

const char *FsrPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_links: return omnetpp::opp_typename(typeid(LinkStateEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr FsrPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_links: return omnetpp::toAnyPtr(&pp->getLinks(i)); break;
        case FIELD_neighborsList: return omnetpp::toAnyPtr(&pp->getNeighborsList(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FsrPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FsrPacket'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

