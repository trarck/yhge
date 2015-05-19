#include "CocosSqliteDAO.h"

USING_NS_CC;
USING_NS_CC_YHGE_SQLITE;

NS_CC_YHGE_DATA_BEGIN

static const char* kSqlSeprate=",";
static const char* kSqlFieldQuto="`";
static const char* kSqlNullValue="null";
static const char* kSqlDefaultPrepareFlag=":";

CocosSqliteDAO::CocosSqliteDAO()
:_driver(NULL)
,_prepareFlag(kSqlDefaultPrepareFlag)
{

}

CocosSqliteDAO::~CocosSqliteDAO()
{
    CC_SAFE_RELEASE_NULL(_driver);
}


bool CocosSqliteDAO::init()
{
    sqlite::SqliteDriver* sqliteDriver=new sqlite::SqliteDriver();
    
    _driver=new CocosSqliteDriver(sqliteDriver);
    
    return true;
}

bool CocosSqliteDAO::init(const std::string& dbPath,int flag)
{
    sqlite::SqliteDriver* sqliteDriver=new sqlite::SqliteDriver();
    
    _driver=new CocosSqliteDriver(sqliteDriver);
    
    sqliteDriver->connect(dbPath,flag);
    
    return true;
}

bool CocosSqliteDAO::init(CocosSqliteDriver* driver)
{
    setDriver(driver);
    
    return true;
}

int CocosSqliteDAO::fetchNumber(const std::string& querySql)
{
    Statement stmt(*(_driver->getPtr()),querySql);
    
    if(stmt.execute()){
        
        Column col=stmt.getColumn(0);
        
        return col.getInt();
    }
    
    return 0;
}

ValueVector CocosSqliteDAO::fetchAll(const std::string& querySql)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    int colCount=stmt.getColumnCount();
    
	ValueVector result ;
    
    while (stmt.executeStep()) {
        
        ValueMap record;
        
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),record);
        }
        
        result.push_back(Value(record));
    }
    
    return result;
    
}

ValueMap CocosSqliteDAO::fetchOne(const std::string& querySql)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    int colCount=stmt.getColumnCount();
    
	ValueMap result;
    
    if (stmt.executeStep()) {
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),result);
        }
    }
    
    return result;
}

int CocosSqliteDAO::insert(const std::string& insertSql)
{
    return _driver->getPtr()->execute(insertSql);
}

int CocosSqliteDAO::update(const std::string& updateSql)
{
    return _driver->getPtr()->execute(updateSql);
}

int CocosSqliteDAO::remove(const std::string& deleteSql)
{
    return _driver->getPtr()->execute(deleteSql);
}

int CocosSqliteDAO::insert(const std::string& table,const ValueMap& data)
{
    //生成sql
    std::string insertSql = "INSERT INTO "+table+" ";
    
    insertSql+=formateToInsertPrepare(data);
    
    insertSql+=";";
    
    Statement stmt(*(_driver->getPtr()), insertSql);
    
	//绑定变量
	for (ValueMap::const_iterator iter = data.begin(); iter != data.end();++iter){
		bindStatement(stmt,iter->first, iter->second);
	}

    return stmt.execute();
}

void CocosSqliteDAO::batchInsert(const std::string& table,const ValueVector& data)
{
    //准备sql
    std::string insertSql = "INSERT INTO "+table+" ";
    
    insertSql+=formateToInsertPrepare(data.front().asValueMap());
    
    insertSql+=";";
    
    //只使用一个statement
    Statement stmt(*(_driver->getPtr()), insertSql);
    
    
    int count=data.size();
    
    for(unsigned int i=0;i<count;++i){
        
        //如果不是第一个使用stmt，要重置下。
        if (i!=0) {
            stmt.reset();
        }
        
        //分别绑定每一条记录
		ValueMap record = data.at(i).asValueMap();
		for (ValueMap::const_iterator iter = record.begin(); iter != record.end(); ++iter){
			bindStatement(stmt, iter->first, iter->second);
		}

        stmt.execute();
    }
}

int CocosSqliteDAO::update(const std::string& table, const ValueMap& data, const ValueMap& where)
{
    //生成sql
    std::string updateSql = "UPDATE "+table+" SET ";
    
    updateSql+=formateToEqualPrepare(data);
    
    //检查有没有更新条件
    if (where==NULL) {
        
        updateSql+=";";
        
        Statement stmt(*(_driver->getPtr()), updateSql);
        
        //绑定更新数据
        CCDictElement* pElem=NULL;
        
        CCDICT_FOREACH(data, pElem) {
            bindStatement(stmt,pElem->getStrKey(),static_cast<SimpleValue*>(pElem->getObject()));
        }
        
        return stmt.execute();
        
    }else{
        //生成where语句
        CCArray* whereData=CCArray::create();
        
        std::string whereSql=formateToConditionPrepare(where, whereData);
        
        updateSql+=" WHERE "+whereSql;
        
        updateSql+=";";
        
        Statement stmt(*(_driver->getPtr()), updateSql);
        
        //由于带标志符的也占用位置，所以问号表示的不是问号中的位置，而是整个参数中的位置。所以要跳过更新数据的变量。
        int i=1;
        
        //绑定更新数据
        CCDictElement* pElem=NULL;
        
        CCDICT_FOREACH(data, pElem) {
            bindStatement(stmt,pElem->getStrKey(),static_cast<SimpleValue*>(pElem->getObject()));
            ++i;
        }
        
        //绑定where数据
        Ref* pObj=NULL;
        CCARRAY_FOREACH(whereData, pObj) {
            bindStatement(stmt,i++,static_cast<SimpleValue*>(pObj));
        }
        
        return stmt.execute();
    }
}

int CocosSqliteDAO::remove(const std::string& table,CCDictionary* where)
{
    //生成sql
    std::string deleteSql = "DELETE FROM "+table+" WHERE ";
    
    CCArray* whereData=CCArray::create();
    
    deleteSql+=formateToConditionPrepare(where,whereData);
    
    deleteSql+=";";
    
    Statement stmt(*(_driver->getPtr()), deleteSql);
    
    //绑定条件数据
    int i=1;
    Ref* pObj=NULL;
    CCARRAY_FOREACH(whereData, pObj) {
        bindStatement(stmt,i++,static_cast<SimpleValue*>(pObj));
    }
    
    return stmt.execute();
}

/*
 
 {
 
 "a":1,
 "b":2,
 "c":3
 }
 
 =>
 
 (`a`,`b`,`c`) values (:a,:b,:c)
 
 
 */
std::string CocosSqliteDAO::formateToInsertPrepare(CCDictionary* data)
{
    
    
    std::string fields="(";
    std::string values="(";
    
    bool isFirst=true;
    
    CCDictElement* pElem=NULL;
    
    CCDICT_FOREACH(data, pElem) {
        
        //如果不是第一项，则加入分割符
        if (isFirst) {
            isFirst=false;
        }else{
            fields+=kSqlSeprate;
            values+=kSqlSeprate;
        }
        //`a`
        fields+= kSqlFieldQuto+ std::string(pElem->getStrKey()) + kSqlFieldQuto;
        
        //:a
        values+= _prepareFlag + pElem->getStrKey();
    }
    
    fields+=")";
    values+=")";
    
    return fields + " values " + values;
}

/*
 
 {
 
 "a":1,
 "b":2,
 "c":3
 }
 
 =>
 
 `a`=:a,`b`=:b,`c`=:c
 
 */
std::string CocosSqliteDAO::formateToEqualPrepare(CCDictionary* data)
{
    std::string prepareStr="";
    
    bool isFirst=true;
    
    CCDictElement* pElem=NULL;
    
    CCDICT_FOREACH(data, pElem) {
        
        //如果不是第一项，则加入分割符
        if (isFirst) {
            isFirst=false;
        }else{
            prepareStr+=kSqlSeprate;
        }
        
        //`a`=:a
        prepareStr+= kSqlFieldQuto+ std::string(pElem->getStrKey()) + kSqlFieldQuto
        + "="
        + _prepareFlag + pElem->getStrKey();
    }
    
    return prepareStr;
}

/*
 由于条件可以嵌套，并且可能会有重复，所以使用?来绑定
 {
 
 "a":1,
 "b":2,
 "c":3
 }
 
 =>
 
 `a`=? AND `b`=? AND `c`=?
 
 {
 
 "a":1,
 
 "OR":{
 "b":2,
 "c":3
 }
 }
 
 `a`=? AND (`b`=? OR `c`=?)
 
 */
std::string CocosSqliteDAO::formateToConditionPrepare(CCDictionary* data,CCArray* whereData,const std::string& separator)
{
    
    std::string prepareStr="";
    
    bool isFirst=true;
    
    CCDictElement* pElem=NULL;
    
    CCDICT_FOREACH(data, pElem) {
        
        std::string key=pElem->getStrKey();
        
        if (isFirst) {
            isFirst=false;
        }else{
            prepareStr+=" "+separator+" ";
        }
        
        if (key=="AND" || key=="OR") {
            
            prepareStr+= "("+formateToConditionPrepare(static_cast<CCDictionary*>(pElem->getObject()),whereData,key)+")";
            
        }else{
            whereData->addObject(pElem->getObject());
            
            //`a`=?
            prepareStr+= kSqlFieldQuto+ key + kSqlFieldQuto + "= ?";
        }
    }
    
    return prepareStr;
}

void CocosSqliteDAO::setRecordValue(const sqlite::Column& col, CCDictionary* record)
{
    switch (col.getType()) {
        case SQLITE_INTEGER:
            record->setObject(SimpleValue::create(col.getInt()), col.getName());
            break;
        case SQLITE_FLOAT:
            record->setObject(SimpleValue::create(col.getDouble()), col.getName());
            break;
        case SQLITE_BLOB:{
            char* blobBegin=(char*)col.getBlob();
            std::string str(blobBegin,col.getBytes());
            record->setObject(SimpleValue::create(str), col.getName());
            break;
        }
        case SQLITE_NULL:
            record->setObject(SimpleValue::create(), col.getName());
            break;
        case SQLITE_TEXT:
            record->setObject(SimpleValue::create(col.getText()), col.getName());
            break;
        default:
            break;
    }
}
//
//void CocosSqliteDAO::bindStatement(Statement& stmt,const std::string& name,Ref* val)
//{
//    CCInteger* integerValue=dynamic_cast<CCInteger*>(val);
//    if (integerValue) {
//        stmt.bind(name, integerValue->getValue());
//        return;
//    }
//    
//    CCString* strValue=dynamic_cast<CCString*>(val);
//    if (strValue) {
//        stmt.bind(name, strValue->getCString());
//        return;
//    }
//    
//    CCFloat* floatValue=dynamic_cast<CCFloat*>(val);
//    if (floatValue) {
//        stmt.bind(name, floatValue->getValue());
//        return;
//    }
//    
//    CCBool* boolValue=dynamic_cast<CCBool*>(val);
//    if (boolValue) {
//        stmt.bind(name, boolValue->getValue()?1:0);
//        return;
//    }
//    
//    if (val==NULL) {
//        stmt.bind(name, kSqlNullValue);
//        return;
//    }
//
//}
//
//void CocosSqliteDAO::bindStatement(Statement& stmt,int index,Ref* val)
//{
//    CCInteger* integerValue=dynamic_cast<CCInteger*>(val);
//    if (integerValue) {
//        stmt.bind(index, integerValue->getValue());
//        return;
//    }
//    
//    CCString* strValue=dynamic_cast<CCString*>(val);
//    if (strValue) {
//        stmt.bind(index, strValue->getCString());
//        return;
//    }
//    
//    CCFloat* floatValue=dynamic_cast<CCFloat*>(val);
//    if (floatValue) {
//        stmt.bind(index, floatValue->getValue());
//        return;
//    }
//    
//    CCBool* boolValue=dynamic_cast<CCBool*>(val);
//    if (boolValue) {
//        stmt.bind(index, boolValue->getValue()?1:0);
//        return;
//    }
//    
//    if (val==NULL) {
//        stmt.bind(index, kSqlNullValue);
//        return;
//    }
//}


void CocosSqliteDAO::bindStatement(Statement& stmt,const std::string& name,SimpleValue* val)
{
    
    switch (val->getType()) {
        case SimpleValue::INTEGER:
            stmt.bind(name, val->asByte());
            break;
        case SimpleValue::BYTE:
            stmt.bind(name, val->asInt());
            break;
        case SimpleValue::STRING:
            stmt.bind(name, val->asString());
            break;
        case SimpleValue::FLOAT:
            stmt.bind(name, val->asFloat());
            break;
        case SimpleValue::DOUBLE:
            stmt.bind(name, val->asDouble());
            break;
        case SimpleValue::BOOLEAN:
            stmt.bind(name, val->asBool()?1:0);
            break;
        case SimpleValue::NONE:
            stmt.bind(name,kSqlNullValue);
            break;
        default:
            break;
    }
}

void CocosSqliteDAO::bindStatement(Statement& stmt,int index,SimpleValue* val)
{
    
    switch (val->getType()) {
        case SimpleValue::INTEGER:
            stmt.bind(index, val->asByte());
            break;
        case SimpleValue::BYTE:
            stmt.bind(index, val->asInt());
            break;
        case SimpleValue::STRING:
            stmt.bind(index, val->asString());
            break;
        case SimpleValue::FLOAT:
            stmt.bind(index, val->asFloat());
            break;
        case SimpleValue::DOUBLE:
            stmt.bind(index, val->asDouble());
            break;
        case SimpleValue::BOOLEAN:
            stmt.bind(index, val->asBool()?1:0);
            break;
        case SimpleValue::NONE:
            stmt.bind(index,kSqlNullValue);
            break;
        default:
            break;
    }
}

NS_CC_YHGE_DATA_END
