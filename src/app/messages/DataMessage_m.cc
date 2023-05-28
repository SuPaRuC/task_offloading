//
// Generated file, do not edit! Created by opp_msgtool 6.0 from app/messages/DataMessage.msg.
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
#include "DataMessage_m.h"

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

namespace task_offloading {

Register_Class(DataMessage)

DataMessage::DataMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

DataMessage::DataMessage(const DataMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

DataMessage::~DataMessage()
{
}

DataMessage& DataMessage::operator=(const DataMessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void DataMessage::copy(const DataMessage& other)
{
    this->loadToProcess = other.loadToProcess;
    this->computationTime = other.computationTime;
    this->hostIndex = other.hostIndex;
    this->partitionId = other.partitionId;
    this->taskId = other.taskId;
    this->loadBalancingId = other.loadBalancingId;
    this->cpi = other.cpi;
    this->senderAddress = other.senderAddress;
}

void DataMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->loadToProcess);
    doParsimPacking(b,this->computationTime);
    doParsimPacking(b,this->hostIndex);
    doParsimPacking(b,this->partitionId);
    doParsimPacking(b,this->taskId);
    doParsimPacking(b,this->loadBalancingId);
    doParsimPacking(b,this->cpi);
    doParsimPacking(b,this->senderAddress);
}

void DataMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->loadToProcess);
    doParsimUnpacking(b,this->computationTime);
    doParsimUnpacking(b,this->hostIndex);
    doParsimUnpacking(b,this->partitionId);
    doParsimUnpacking(b,this->taskId);
    doParsimUnpacking(b,this->loadBalancingId);
    doParsimUnpacking(b,this->cpi);
    doParsimUnpacking(b,this->senderAddress);
}

double DataMessage::getLoadToProcess() const
{
    return this->loadToProcess;
}

void DataMessage::setLoadToProcess(double loadToProcess)
{
    this->loadToProcess = loadToProcess;
}

double DataMessage::getComputationTime() const
{
    return this->computationTime;
}

void DataMessage::setComputationTime(double computationTime)
{
    this->computationTime = computationTime;
}

int DataMessage::getHostIndex() const
{
    return this->hostIndex;
}

void DataMessage::setHostIndex(int hostIndex)
{
    this->hostIndex = hostIndex;
}

int DataMessage::getPartitionId() const
{
    return this->partitionId;
}

void DataMessage::setPartitionId(int partitionId)
{
    this->partitionId = partitionId;
}

int DataMessage::getTaskId() const
{
    return this->taskId;
}

void DataMessage::setTaskId(int taskId)
{
    this->taskId = taskId;
}

int DataMessage::getLoadBalancingId() const
{
    return this->loadBalancingId;
}

void DataMessage::setLoadBalancingId(int loadBalancingId)
{
    this->loadBalancingId = loadBalancingId;
}

int DataMessage::getCpi() const
{
    return this->cpi;
}

void DataMessage::setCpi(int cpi)
{
    this->cpi = cpi;
}

const ::veins::LAddress::L2Type& DataMessage::getSenderAddress() const
{
    return this->senderAddress;
}

void DataMessage::setSenderAddress(const ::veins::LAddress::L2Type& senderAddress)
{
    this->senderAddress = senderAddress;
}

class DataMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_loadToProcess,
        FIELD_computationTime,
        FIELD_hostIndex,
        FIELD_partitionId,
        FIELD_taskId,
        FIELD_loadBalancingId,
        FIELD_cpi,
        FIELD_senderAddress,
    };
  public:
    DataMessageDescriptor();
    virtual ~DataMessageDescriptor();

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

Register_ClassDescriptor(DataMessageDescriptor)

DataMessageDescriptor::DataMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(task_offloading::DataMessage)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

DataMessageDescriptor::~DataMessageDescriptor()
{
    delete[] propertyNames;
}

bool DataMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DataMessage *>(obj)!=nullptr;
}

const char **DataMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DataMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DataMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int DataMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_loadToProcess
        FD_ISEDITABLE,    // FIELD_computationTime
        FD_ISEDITABLE,    // FIELD_hostIndex
        FD_ISEDITABLE,    // FIELD_partitionId
        FD_ISEDITABLE,    // FIELD_taskId
        FD_ISEDITABLE,    // FIELD_loadBalancingId
        FD_ISEDITABLE,    // FIELD_cpi
        0,    // FIELD_senderAddress
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *DataMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "loadToProcess",
        "computationTime",
        "hostIndex",
        "partitionId",
        "taskId",
        "loadBalancingId",
        "cpi",
        "senderAddress",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int DataMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "loadToProcess") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "computationTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hostIndex") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "partitionId") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "taskId") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "loadBalancingId") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "cpi") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "senderAddress") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *DataMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_loadToProcess
        "double",    // FIELD_computationTime
        "int",    // FIELD_hostIndex
        "int",    // FIELD_partitionId
        "int",    // FIELD_taskId
        "int",    // FIELD_loadBalancingId
        "int",    // FIELD_cpi
        "veins::LAddress::L2Type",    // FIELD_senderAddress
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **DataMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *DataMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int DataMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DataMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DataMessage'", field);
    }
}

const char *DataMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DataMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        case FIELD_loadToProcess: return double2string(pp->getLoadToProcess());
        case FIELD_computationTime: return double2string(pp->getComputationTime());
        case FIELD_hostIndex: return long2string(pp->getHostIndex());
        case FIELD_partitionId: return long2string(pp->getPartitionId());
        case FIELD_taskId: return long2string(pp->getTaskId());
        case FIELD_loadBalancingId: return long2string(pp->getLoadBalancingId());
        case FIELD_cpi: return long2string(pp->getCpi());
        case FIELD_senderAddress: return "";
        default: return "";
    }
}

void DataMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        case FIELD_loadToProcess: pp->setLoadToProcess(string2double(value)); break;
        case FIELD_computationTime: pp->setComputationTime(string2double(value)); break;
        case FIELD_hostIndex: pp->setHostIndex(string2long(value)); break;
        case FIELD_partitionId: pp->setPartitionId(string2long(value)); break;
        case FIELD_taskId: pp->setTaskId(string2long(value)); break;
        case FIELD_loadBalancingId: pp->setLoadBalancingId(string2long(value)); break;
        case FIELD_cpi: pp->setCpi(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DataMessage'", field);
    }
}

omnetpp::cValue DataMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        case FIELD_loadToProcess: return pp->getLoadToProcess();
        case FIELD_computationTime: return pp->getComputationTime();
        case FIELD_hostIndex: return pp->getHostIndex();
        case FIELD_partitionId: return pp->getPartitionId();
        case FIELD_taskId: return pp->getTaskId();
        case FIELD_loadBalancingId: return pp->getLoadBalancingId();
        case FIELD_cpi: return pp->getCpi();
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DataMessage' as cValue -- field index out of range?", field);
    }
}

void DataMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        case FIELD_loadToProcess: pp->setLoadToProcess(value.doubleValue()); break;
        case FIELD_computationTime: pp->setComputationTime(value.doubleValue()); break;
        case FIELD_hostIndex: pp->setHostIndex(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_partitionId: pp->setPartitionId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_taskId: pp->setTaskId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_loadBalancingId: pp->setLoadBalancingId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_cpi: pp->setCpi(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DataMessage'", field);
    }
}

const char *DataMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr DataMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DataMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DataMessage *pp = omnetpp::fromAnyPtr<DataMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DataMessage'", field);
    }
}

}  // namespace task_offloading

namespace omnetpp {

}  // namespace omnetpp

