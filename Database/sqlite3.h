#ifndef SQLITE3_MINIMAL_H
#define SQLITE3_MINIMAL_H

// Minimal subset of the SQLite3 header needed for basic open/exec/close calls.
// This is not a full replacement for the official sqlite3.h.

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;

#define SQLITE_OK 0
#define SQLITE_ROW 100

int sqlite3_open(const char *filename, sqlite3 **ppDb);
const char *sqlite3_errmsg(sqlite3 *db);
int sqlite3_exec(sqlite3 *db, const char *sql,
				 int (*callback)(void *, int, char **, char **),
				 void *arg, char **errmsg);
void sqlite3_free(void *ptr);
int sqlite3_close(sqlite3 *db);
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte,
					   sqlite3_stmt **ppStmt, const char **pzTail);
int sqlite3_step(sqlite3_stmt *pStmt);
int sqlite3_column_int(sqlite3_stmt *pStmt, int iCol);
const unsigned char *sqlite3_column_text(sqlite3_stmt *pStmt, int iCol);
double sqlite3_column_double(sqlite3_stmt *pStmt, int iCol);
int sqlite3_finalize(sqlite3_stmt *pStmt);

#ifdef __cplusplus
}
#endif

#endif // SQLITE3_MINIMAL_H
