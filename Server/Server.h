#pragma once

/* VARI�VEIS DO EXECUT�VEL */
#define PSTALE 0x08B67000

// Total de itens no servidor.
#define ITEM_QUANTITY 1689

// Configura��es do SQL.
#define SQL_INST "PT\\SQLExpress"
#define SQL_USER "sa"
#define SQL_PASS "123456"

/* MUDAR: SE FOR O MATEUS COLOQUE // ATRAS DE #DEFINE */
//#define CAINAN

#ifdef CAINAN
#undef SQL_INST
#define SQL_INST "TPT\\SQLExpress"
#endif

// Total de mapas poss�veis.
#define MAX_TOTAL_FIELD 64