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

typedef unsigned int  VOS_UINT32;
typedef int           VOS_INT32;
typedef char          VOS_CHA;
typedef unsigned char VOS_UINT8;
typedef unsigned long VOS_UINT64;

typedef enum {
    ENUM_CHAR,
    ENUM_INT,
} ENUM_COL_TYPE;

int main()
{
    VOS_INT32  dwRetVal = VOS_OK;
    MYSQL      *pMysqlHandler = VOS_NULL;
    MYSQL_RES  *pMysqlResult  = VOS_NULL;
    VOS_UINT32 udwNumFields = VOS_NULL;
    MYSQL_ROW  row;
    VOS_UINT32 udwRowNum = VOS_NULL;
    VOS_UINT32 udwRowIndex = VOS_NULL;
    VOS_UINT64 *puddwLengths = VOS_NULL;
    VOS_UINT32 udwFieldIndex = VOS_NULL;

    pMysqlHandler = mysql_init(VOS_NULL);
    if(VOS_NULL == pMysqlHandler)
    {
        printf("mysql init failed");
        return 1;
    }
    pMysqlHandler = mysql_real_connect(pMysqlHandler, "localhost",
                                       "root", "123456", "menagerie",
                                       VOS_NULL, VOS_NULL, VOS_NULL);

    dwRetVal = mysql_query(pMysqlHandler, "select * from pet;");
    printf("ret_val = %d\n", dwRetVal);

    pMysqlResult = mysql_store_result(pMysqlHandler);
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

    return 0;
}
