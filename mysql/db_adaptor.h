#define MAX_COL_NAME_LEN    50
#define MAX_TABLE_NAME_LEN  50
#define MAX_COL_NUM         50
#define MAX_TABLE_NUM       50

typedef enum {
    ENUM_COL_CHAR,
    ENUM_COL_INT,

    ENUM_COL_BUTT
} ENUM_COL_TYPE;

typedef struct ST_COL_ATTR {
    unsigned int    col_index;
    unsigned int    col_type;
    unsigned int    offset;
    char            sz_col_name[MAX_COL_NAME_LEN + 1];
} ST_COL_ATTR;

typedef struct ST_TABLE_INFO {
    unsigned int    table_id;
    unsigned int    col_num;
    char            sz_table_name[MAX_TABLE_NAME_LEN + 1];
    ST_COL_ATTR     ast_col_attr[MAX_COL_NUM];
} ST_TABLE_INFO;

#define DB_ADD_COL_ATTR(added_index, added_type, added_offset, added_name) \
    if(col_num >= MAX_COL_NAME_LEN) \
    { \
        return; \
    } \
    g_ast_table_info[index].ast_col_attr[col_num].col_index = added_index; \
    g_ast_table_info[index].ast_col_attr[col_num].col_type = added_type;  \
    g_ast_table_info[index].ast_col_attr[col_num].offset = added_offset;    \
    strcpy(g_ast_table_info[index].ast_col_attr[col_num].sz_col_name,  added_name); \
    col_num++;

#define DB_SUCCESS  0
#define DB_ERR_TABLE_ID  1
#define DB_ERR_COL_NUM  2



#define TABLE_PET       1
#define TABLE_PET_NAME  "pet"

#define COL_PET_NAME    0
#define COL_PET_OWNER   1
#define COL_PET_SPECIES 2
#define COL_PET_SEX     3
#define COL_PET_BIRTH   4
#define COL_PET_DEATH   5

#define PET_NAME_LEN    20
#define PET_OWNER_LEN   20
#define PET_SPECIES_LEN 20
#define PET_SEX_LEN     1
#define PET_BIRTH_LEN   10
#define PET_DEATH_LEN   10

typedef struct ST_PET {
    char    szName[PET_NAME_LEN + 1];
    char    szOwner[PET_OWNER_LEN + 1];
    char    szSpecies[PET_SPECIES_LEN + 1];
    char    szSex[PET_SEX_LEN + 1];
    char    szBirth[PET_BIRTH_LEN + 1];
    char    szDeath[PET_DEATH_LEN + 1];
} ST_PET;