#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "db_adaptor.h"

ST_TABLE_INFO g_ast_table_info[MAX_TABLE_NUM];

void db_init_table_info()
{
	memset(g_ast_table_info, 0, sizeof(g_ast_table_info));

	return;
}

int db_get_idle_table_info()
{
	int index = 0;
	for(index = 0; index < MAX_TABLE_NUM; index++)
	{
		if(0 == g_ast_table_info[index].col_num)
		{
			return index;
		}
	}

	return MAX_TABLE_NUM;
}

void db_add_pet_table_info()
{

	int index = 0;
	int col_num = 0;

	index = db_get_idle_table_info();
	if(index >= MAX_TABLE_NUM)
	{
		return;
	}

	g_ast_table_info[index].table_id = TABLE_PET;
	strcpy(g_ast_table_info[index].sz_table_name, TABLE_PET_NAME);

	DB_ADD_COL_ATTR(COL_PET_NAME, 	 ENUM_COL_CHAR, offsetof(ST_PET, szName), 	 "name");
	DB_ADD_COL_ATTR(COL_PET_OWNER, 	 ENUM_COL_CHAR, offsetof(ST_PET, szOwner),   "owner");
	DB_ADD_COL_ATTR(COL_PET_SPECIES, ENUM_COL_CHAR, offsetof(ST_PET, szSpecies), "species");
	DB_ADD_COL_ATTR(COL_PET_SEX,     ENUM_COL_CHAR, offsetof(ST_PET, szSex),     "sex");
	DB_ADD_COL_ATTR(COL_PET_BIRTH,   ENUM_COL_CHAR, offsetof(ST_PET, szBirth),   "birth");
	DB_ADD_COL_ATTR(COL_PET_DEATH,   ENUM_COL_CHAR, offsetof(ST_PET, szDeath),   "death");

	g_ast_table_info[index].col_num = col_num;

	return;
}

ST_TABLE_INFO *db_get_table_info(unsigned int table_id)
{
	int index = 0;

	for(index = 0; index < MAX_TABLE_NUM; index++)
	{
		if(table_id == g_ast_table_info[index].table_id)
		{
			return &(g_ast_table_info[index]);
		}
	}

	return NULL;
}

int db_add_item(unsigned int table_id, void *p_data)
{
	char sz_cols[2000] = {0};
	char sz_values[2000] = {0};
	int cols_offset = 0;
	int values_offset = 0;
	int len = 0;
	int col_index = 0;
	ST_TABLE_INFO 	*pst_table_info = NULL;
	ST_COL_ATTR 	*pst_col_attr 	= NULL;
	
	/* 根据table id获取table info */
	pst_table_info = db_get_table_info(table_id);
	if(NULL == pst_table_info)
	{
		return DB_ERR_TABLE_ID;
	}

	if(0 == pst_table_info->col_num || pst_table_info->col_num > MAX_COL_NUM)
	{
		return DB_ERR_COL_NUM;
	}

	
	for(col_index = 0; col_index < pst_table_info->col_num; col_index++)
	{
		pst_col_attr = &(pst_table_info->ast_col_attr[col_index]);
		/* 拼接col_name */
		if(0 != col_index)
		{
			len = sprintf(sz_cols + cols_offset, "%s", ", ");
			cols_offset += len;
		}
		len = sprintf(sz_cols + cols_offset, "%s", pst_col_attr->sz_col_name);
		cols_offset += len;

		/* 拼接values */
		if(0 != col_index)
		{
			len = sprintf(sz_values + values_offset, "%s", ", ");
			values_offset += len;
		}
		switch(pst_col_attr->col_type)
		{
			case ENUM_COL_CHAR:
			{
				len = sprintf(sz_values + values_offset, "%s", (char *)(p_data + pst_col_attr->offset));
				values_offset += len;
				break;
			}
			case ENUM_COL_INT:
			{
				len = sprintf(sz_values + values_offset, "%d", *(int *)(p_data + pst_col_attr->offset));
				values_offset += len;
				break;
			}
			default:
			{
				printf("unknown col type = %d", pst_col_attr->col_type);
				len = 0;
			}
		}
	}

	printf("sz_cols = %s\n", sz_cols);
	printf("sz_values = %s\n", sz_values);
}


int main()
{
	ST_PET stPet;

	strcpy(stPet.szName, "Fluffy");
	strcpy(stPet.szOwner, "Harold");
	strcpy(stPet.szSpecies, "cat");
	strcpy(stPet.szSex, "f");
	strcpy(stPet.szBirth, "1993-02-04");

	db_init_table_info();

	db_add_pet_table_info();

	db_add_item(TABLE_PET, &stPet);
}