#include <iostream>
#include "sqlite3.h"

int main() {
	sqlite3 *db = nullptr;
	const char *dbPath = "school.db";

	if (sqlite3_open(dbPath, &db) != SQLITE_OK) {
		std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << "\n";
		return 1;
	}

	const char *createTableSql =
		"CREATE TABLE IF NOT EXISTS Tasks ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT NOT NULL,"
		"description TEXT"
		");";

	const char *dropAssignmentsSql = "DROP TABLE IF EXISTS Assignments;";
	const char *createAssignmentsSql =
		"CREATE TABLE IF NOT EXISTS Assignments ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_task INTEGER NOT NULL,"
		"id_course TEXT NOT NULL"
		");";

	const char *createCoursesSql =
		"CREATE TABLE IF NOT EXISTS Courses ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT NOT NULL,"
		"description TEXT"
		");";

	const char *createStudentsSql =
		"CREATE TABLE IF NOT EXISTS Students ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT NOT NULL,"
		"birthday TEXT,"
		"major TEXT"
		");";

	const char *createCompletionSql =
		"CREATE TABLE IF NOT EXISTS Completion ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_assignment INTEGER NOT NULL,"
		"id_student INTEGER NOT NULL,"
		"time TEXT"
		");";

	const char *createCreditsSql =
		"CREATE TABLE IF NOT EXISTS Credits ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_course INTEGER NOT NULL,"
		"id_student INTEGER NOT NULL,"
		"date TEXT,"
		"grade INTEGER,"
		"credits TEXT"
		");";

	char *errMsg = nullptr;
	if (sqlite3_exec(db, createTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to create Tasks table: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	if (sqlite3_exec(db, dropAssignmentsSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to drop Assignments table: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	if (sqlite3_exec(db, createAssignmentsSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to create Assignments table: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	if (sqlite3_exec(db, createCoursesSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to create Courses table: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	if (sqlite3_exec(db, createStudentsSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to create Students table: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	if (sqlite3_exec(db, createCompletionSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to create Completion table: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	if (sqlite3_exec(db, createCreditsSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to create Credits table: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	
	const char *insertSql =
		"INSERT OR REPLACE INTO Tasks (id, name, description) VALUES "
		"(1, 'Dtabase', 'Create a database for school assignments');"
		"INSERT OR REPLACE INTO Tasks (id, name, description) VALUES "
		"(2, 'Webpage', 'Create a Webpage for portfolio');"
		"INSERT OR REPLACE INTO Assignments (id, id_task, id_course) VALUES "
		"(1, 1, 'Database Management');"
		"INSERT OR REPLACE INTO Assignments (id, id_task, id_course) VALUES "
		"(2, 2, 'Web Development');"
		"INSERT OR REPLACE INTO Courses (id, name, description) VALUES "
		"(1, 'Database Management', 'Introduction to Database Management');"
		"INSERT OR REPLACE INTO Courses (id, name, description) VALUES "
		"(2, 'Web Development', 'Creating simple websites');"
		"INSERT OR REPLACE INTO Courses (id, name, description) VALUES "
		"(3, 'Programming Fundamentals', 'Introduction to programming)');"
		"INSERT OR REPLACE INTO Students (id, name, birthday, major) VALUES "
		"(1, 'Johnson', '2003-04-15', 'Computer Science');"
		"INSERT OR REPLACE INTO Students (id, name, birthday, major) VALUES "
		"(2, 'Anne', '1996-11-02', 'Information Technology');"
		"INSERT OR REPLACE INTO Students (id, name, birthday, major) VALUES "
		"(3, 'Carter', '2000-02-28', 'Software Engineering)');"
		"INSERT OR REPLACE INTO Completion (id, id_assignment, id_student, time) VALUES "
		"(1, 1, 1, '12.38 2025.01.10');"
		"INSERT OR REPLACE INTO Completion (id, id_assignment, id_student, time) VALUES "
		"(2, 1, 2, '19.24 2025.01.10');"
		"INSERT OR REPLACE INTO Completion (id, id_assignment, id_student, time) VALUES "
		"(3, 2, 3, '23.25 2025.01.10');"
		"INSERT OR REPLACE INTO Completion (id, id_assignment, id_student, time) VALUES "
		"(4, 2, 3, '08.34 2025.01.11');"
		"INSERT OR REPLACE INTO Credits (id, id_course, id_student, date, grade, credits) VALUES "
		"(1, 1, 1, '2025-01-15', 5, '3');"
		"INSERT OR REPLACE INTO Credits (id, id_course, id_student, date, grade, credits) VALUES "
		"(2, 1, 2, '2025-01-15', 4, '3');"
		"INSERT OR REPLACE INTO Credits (id, id_course, id_student, date, grade, credits) VALUES "
		"(3, 2, 2, '2025-01-20', 5, '4');"
		"INSERT OR REPLACE INTO Credits (id, id_course, id_student, date, grade, credits) VALUES "
		"(4, 3, 3, '2025-01-25', 3, '3');";

	if (sqlite3_exec(db, insertSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Failed to insert seed data: " << (errMsg ? errMsg : "unknown error") << "\n";
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return 1;
	}

	// Query to list all assignments with their related tasks and courses
		
	const char *querySql =
		"SELECT a.id, t.name AS task_name, a.id_course AS course_name "
		"FROM Assignments a "
		"JOIN Tasks t ON a.id_task = t.id;";

	sqlite3_stmt *stmt = nullptr;
	std::cout << "\n=== Assignments with Related Tasks and Courses ===\n" << std::flush;
	std::cout << "Assignment ID | Task Name | Course Name\n" << std::flush;
	std::cout << "--------------|-----------|------------\n" << std::flush;

	if (sqlite3_prepare_v2(db, querySql, -1, &stmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int assignmentId = sqlite3_column_int(stmt, 0);
			const char *taskName = (const char *)sqlite3_column_text(stmt, 1);
			const char *courseName = (const char *)sqlite3_column_text(stmt, 2);
			std::cout << assignmentId << " | " << taskName << " | " << courseName << "\n" << std::flush;
		}
		sqlite3_finalize(stmt);
	} else {
		std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}
	

	// Query to show all completions with assignment details and task names
		
	const char *completionQuery =
		"SELECT c.id, c.time, c.id_assignment, t.name AS task_name "
		"FROM Completion c "
		"JOIN Assignments a ON c.id_assignment = a.id "
		"JOIN Tasks t ON a.id_task = t.id;";

	sqlite3_stmt *completionStmt = nullptr;
	std::cout << "\nCompletions with Assignment Details\n" << std::flush;
	std::cout << "Completion ID | Time | Assignment ID | Task Name\n" << std::flush;
	std::cout << "--------------|------|---------------|----------\n" << std::flush;

	if (sqlite3_prepare_v2(db, completionQuery, -1, &completionStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(completionStmt) == SQLITE_ROW) {
			int completionId = sqlite3_column_int(completionStmt, 0);
			const char *time = (const char *)sqlite3_column_text(completionStmt, 1);
			int assignmentId = sqlite3_column_int(completionStmt, 2);
			const char *taskName = (const char *)sqlite3_column_text(completionStmt, 3);
			std::cout << completionId << " | " << time << " | " << assignmentId << " | " << taskName << "\n" << std::flush;
		}
		sqlite3_finalize(completionStmt);
	} else {
		std::cerr << "Failed to prepare completion query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}
	

	// Query to list students with their courses and grades
		
	const char *studentGradesQuery =
		"SELECT s.name AS student_name, c.name AS course_name, cr.grade, cr.credits "
		"FROM Credits cr "
		"JOIN Students s ON cr.id_student = s.id "
		"JOIN Courses c ON cr.id_course = c.id;";

	sqlite3_stmt *gradesStmt = nullptr;
	std::cout << "\n=== Students with Courses and Grades ===\n" << std::flush;
	std::cout << "Student Name | Course Name | Grade | Credits\n" << std::flush;
	std::cout << "-------------|-------------|-------|--------\n" << std::flush;

	if (sqlite3_prepare_v2(db, studentGradesQuery, -1, &gradesStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(gradesStmt) == SQLITE_ROW) {
			const char *studentName = (const char *)sqlite3_column_text(gradesStmt, 0);
			const char *courseName = (const char *)sqlite3_column_text(gradesStmt, 1);
			int grade = sqlite3_column_int(gradesStmt, 2);
			const char *credits = (const char *)sqlite3_column_text(gradesStmt, 3);
			std::cout << studentName << " | " << courseName << " | " << grade << " | " << credits << "\n" << std::flush;
		}
		sqlite3_finalize(gradesStmt);
	} else {
		std::cerr << "Failed to prepare student grades query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}
	

	// Query to find all tasks completed by students
		
	const char *completedTasksQuery =
		"SELECT s.name AS student_name, t.name AS task_name, c.time "
		"FROM Completion c "
		"JOIN Students s ON c.id_student = s.id "
		"JOIN Assignments a ON c.id_assignment = a.id "
		"JOIN Tasks t ON a.id_task = t.id;";

	sqlite3_stmt *completedStmt = nullptr;
	std::cout << "\n=== Tasks Completed by Students ===\n" << std::flush;
	std::cout << "Student Name | Task Name | Completion Time\n" << std::flush;
	std::cout << "-------------|-----------|----------------\n" << std::flush;

	if (sqlite3_prepare_v2(db, completedTasksQuery, -1, &completedStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(completedStmt) == SQLITE_ROW) {
			const char *studentName = (const char *)sqlite3_column_text(completedStmt, 0);
			const char *taskName = (const char *)sqlite3_column_text(completedStmt, 1);
			const char *time = (const char *)sqlite3_column_text(completedStmt, 2);
			std::cout << studentName << " | " << taskName << " | " << time << "\n" << std::flush;
		}
		sqlite3_finalize(completedStmt);
	} else {
		std::cerr << "Failed to prepare completed tasks query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}
	

	// Query to show courses and the number of assignments in each
	
	const char *courseAssignmentsQuery =
		"SELECT a.id_course AS course_name, COUNT(*) AS assignment_count "
		"FROM Assignments a "
		"GROUP BY a.id_course;";

	sqlite3_stmt *courseStmt = nullptr;
	std::cout << "\n=== Courses and Assignment Counts ===\n" << std::flush;
	std::cout << "Course Name | Assignment Count\n" << std::flush;
	std::cout << "------------|------------------\n" << std::flush;

	if (sqlite3_prepare_v2(db, courseAssignmentsQuery, -1, &courseStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(courseStmt) == SQLITE_ROW) {
			const char *courseName = (const char *)sqlite3_column_text(courseStmt, 0);
			int assignmentCount = sqlite3_column_int(courseStmt, 1);
			std::cout << courseName << " | " << assignmentCount << "\n" << std::flush;
		}
		sqlite3_finalize(courseStmt);
	} else {
		std::cerr << "Failed to prepare course assignments query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}
	

	// Query to find courses without assignments using LEFT JOIN and WHERE IS NULL
		
	const char *coursesWithoutAssignmentsQuery =
		"SELECT c.name AS course_name, c.description "
		"FROM Courses c "
		"LEFT JOIN Assignments a ON c.name = a.id_course "
		"WHERE a.id IS NULL;";

	sqlite3_stmt *noAssignStmt = nullptr;
	std::cout << "\n=== Courses Without Assignments ===\n" << std::flush;
	std::cout << "Course Name | Course Description\n" << std::flush;
	std::cout << "------------|-------------------\n" << std::flush;

	if (sqlite3_prepare_v2(db, coursesWithoutAssignmentsQuery, -1, &noAssignStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(noAssignStmt) == SQLITE_ROW) {
			const char *courseName = (const char *)sqlite3_column_text(noAssignStmt, 0);
			const char *description = (const char *)sqlite3_column_text(noAssignStmt, 1);
			std::cout << courseName << " | " << (description ? description : "N/A") << "\n" << std::flush;
		}
		sqlite3_finalize(noAssignStmt);
	} else {
		std::cerr << "Failed to prepare courses without assignments query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}
	

	// Query to show all tables in the database
	const char *showTablesQuery = "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;";
	
	sqlite3_stmt *tablesStmt = nullptr;
	std::cout << "\n=== All Tables in Database ===\n" << std::flush;
	
	if (sqlite3_prepare_v2(db, showTablesQuery, -1, &tablesStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(tablesStmt) == SQLITE_ROW) {
			const char *tableName = (const char *)sqlite3_column_text(tablesStmt, 0);
			std::cout << tableName << "\n" << std::flush;
		}
		sqlite3_finalize(tablesStmt);
	} else {
		std::cerr << "Failed to query tables: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}

	
	// Query to find assignments completed late (after '12.00 2025-01-10')
	
	const char *lateAssignmentsQuery =
		"SELECT c.id_assignment, t.name AS task_name, c.time "
		"FROM Completion c "
		"JOIN Assignments a ON c.id_assignment = a.id "
		"JOIN Tasks t ON a.id_task = t.id "
		"WHERE c.time > '12.00 2025.01.10';";

	sqlite3_stmt *lateStmt = nullptr;
	std::cout << "\n=== Assignments Completed Late ===\n" << std::flush;
	std::cout << "Assignment ID | Task Name | Completion Time\n" << std::flush;
	std::cout << "--------------|-----------|----------------\n" << std::flush;

	if (sqlite3_prepare_v2(db, lateAssignmentsQuery, -1, &lateStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(lateStmt) == SQLITE_ROW) {
			int assignmentId = sqlite3_column_int(lateStmt, 0);
			const char *taskName = (const char *)sqlite3_column_text(lateStmt, 1);
			const char *time = (const char *)sqlite3_column_text(lateStmt, 2);
			std::cout << assignmentId << " | " << taskName << " | " << time << "\n" << std::flush;
		}
		sqlite3_finalize(lateStmt);
	} else {
		std::cerr << "Failed to prepare late assignments query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}

	// Query for Course Performance Summary
	
	const char *coursePerformanceQuery =
		"SELECT c.name AS course_name, COUNT(DISTINCT cr.id_student) AS total_students, "
		"AVG(cr.grade) AS average_grade, SUM(CAST(cr.credits AS INTEGER)) AS total_credits "
		"FROM Courses c "
		"JOIN Credits cr ON c.id = cr.id_course "
		"GROUP BY c.name;";

	sqlite3_stmt *perfStmt = nullptr;
	std::cout << "\n=== Course Performance Summary ===\n" << std::flush;
	std::cout << "Course Name | Total Students | Average Grade | Total Credits\n" << std::flush;
	std::cout << "------------|----------------|---------------|---------------\n" << std::flush;

	if (sqlite3_prepare_v2(db, coursePerformanceQuery, -1, &perfStmt, nullptr) == SQLITE_OK) {
		while (sqlite3_step(perfStmt) == SQLITE_ROW) {
			const char *courseName = (const char *)sqlite3_column_text(perfStmt, 0);
			int totalStudents = sqlite3_column_int(perfStmt, 1);
			double avgGrade = sqlite3_column_double(perfStmt, 2);
			int totalCredits = sqlite3_column_int(perfStmt, 3);
			std::cout << courseName << " | " << totalStudents << " | " << avgGrade << " | " << totalCredits << "\n" << std::flush;
		}
		sqlite3_finalize(perfStmt);
	} else {
		std::cerr << "Failed to prepare course performance query: " << sqlite3_errmsg(db) << "\n" << std::flush;
	}
	

	std::cout << "\nDatabase initialized and Tasks table is ready in '" << dbPath << "'.\n";
	sqlite3_close(db);
	return 0;
}
