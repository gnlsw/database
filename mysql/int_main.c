#include <stdio.h>
#include <mysql/mysql.h>

#define VOS_NULL    0
#define VOS_OK      0
#define VOS_ERROR   1
#define VOS_SUCCESS 0
#define VOS_FAILURE 1

#define VOS_COL_NAME    0
#define VOS_COL_OWNER   1
#define VOS_COL_SPECIES 2
#define VOS_COL_SEX     3
#define VOS_COL_BIRTH   4
#define VOS_COL_DEATH   5

#define VOS_VOID void

typedef unsigned int  VOS_UINT32;
typedef int           VOS_INT32;
typedef char          VOS_CHAR;
typedef unsigned char VOS_UINT8;
typedef unsigned long VOS_UINT64;

typedef enum {
    ENUM_CHAR,
    ENUM_INT,
} ENUM_COL_TYPE;

MYSQL *OpenDatabase();
VOS_VOID VOS_SqlQuery(MYSQL *pMysqlHandler, VOS_CHAR *pcStmt);

int main()
{
    MYSQL      *pMysqlHandler = VOS_NULL;

    pMysqlHandler = OpenDatabase();
    if(VOS_NULL == pMysqlHandler)
    {
        return VOS_FAILURE;
    }

    VOS_SqlQuery(pMysqlHandler, "show databases");
    printf("\n");
    VOS_SqlQuery(pMysqlHandler, "show tables");
    printf("\n");
    /* 测试语句错误 */
    VOS_SqlQuery(pMysqlHandler, "SELECT * from pets");
    printf("\n");
    /* 测试删除语句 */
    VOS_SqlQuery(pMysqlHandler, "DELETE from pet");
    printf("\n");
    /* 测试插入语句 */
    VOS_SqlQuery(pMysqlHandler, "INSERT INTO pet (name, owner, species, sex, birth, death) VALUES ('Fluffy', 'Harold', 'cat', 'f', '1993-02-04', NULL)");
    printf("\n");
    VOS_SqlQuery(pMysqlHandler, "INSERT INTO pet (name, owner, species, sex, birth, death) VALUES ('Fluffy', 'Harold', 'cat', 'f', '1993-02-04', NULL)");
    printf("\n");
    /* 测试查询语句 */
    VOS_SqlQuery(pMysqlHandler, "SELECT * from pet");
    printf("\n");

    return 0;
}

MYSQL *OpenDatabase()
{
    MYSQL      *pHandler = VOS_NULL;

    pHandler = mysql_init(VOS_NULL);
    if(VOS_NULL == pHandler)
    {
        printf("mysql init failed");
        return VOS_NULL;
    }

    if(VOS_NULL == mysql_real_connect(pHandler, "localhost", "root", "123456", "menagerie", 
                        VOS_NULL, VOS_NULL, VOS_NULL))
    {
        printf("mysql real connect failed");
        return VOS_NULL;
    }

    return pHandler;
}

VOS_VOID VOS_SqlQuery(MYSQL *pMysqlHandler, VOS_CHAR *pcStmt)
{
    VOS_INT32  dwRetVal = VOS_OK;
    MYSQL_RES  *pMysqlResult  = VOS_NULL;
    VOS_UINT32 udwNumFields = VOS_NULL;
    MYSQL_ROW  row;
    VOS_UINT32 udwRowNum = VOS_NULL;
    VOS_UINT32 udwRowIndex = VOS_NULL;
    VOS_UINT64 *puddwLengths = VOS_NULL;
    VOS_UINT32 udwFieldIndex = VOS_NULL;

    dwRetVal = mysql_query(pMysqlHandler, pcStmt);
    printf("%s, ret_val = %d\n", pcStmt, dwRetVal);
    if(VOS_SUCCESS != dwRetVal)
    {
        printf("mysql_query failed, ret val = %d\n", dwRetVal);
        return;
    }

    pMysqlResult = mysql_store_result(pMysqlHandler);
    if(VOS_NULL == pMysqlResult)
    {
        printf("MYSQL RES is NULL\n");
        return;
    }

    udwRowNum = mysql_num_rows(pMysqlResult);
    printf("row num = %u\n", udwRowNum); 

    udwNumFields = mysql_num_fields(pMysqlResult);
    for(udwRowIndex = 1; udwRowIndex <= udwRowNum; udwRowIndex++)
    {
        row = mysql_fetch_row(pMysqlResult);
        puddwLengths = mysql_fetch_lengths(pMysqlResult);
        for(udwFieldIndex = 0; udwFieldIndex < udwNumFields; udwFieldIndex++)
        {
            printf("col %d , length is %lu, value = %s\n", udwFieldIndex, puddwLengths[udwFieldIndex], row[udwFieldIndex]);
        }
    }

    mysql_free_result(pMysqlResult);
}
