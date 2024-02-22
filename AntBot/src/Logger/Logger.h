#pragma once

#include <stdexcept>

#ifndef _DEBUG
#define NO_WARN_LOG
#define NO_INFO_LOG
#define NO_DEBUG_LOG
#define NO_TRACE_LOG
#endif

#ifndef LOG_STREAM
#define LOG_STREAM std::cout
#endif

namespace Logger {
	enum LogLevel {
		Fatal,
		Error,
		Warn,
		Info,
		Debug,
		Trace
	};

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#ifdef LOGGER_VERBOSE

#ifdef NO_FATAL_LOG
	#define FATAL_LOG(msg)
#else
	#define FATAL_LOG(msg) LOG_STREAM << __TIME__ << "(" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::hConsole, 13); \
			LOG_STREAM << "FATAL"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_FATAL_LOG
#ifdef NO_ERROR_LOG
	#define ERROR_LOG(msg)
#else
	#define ERROR_LOG(msg) LOG_STREAM << __TIME__ << "(" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::hConsole, 12); \
			LOG_STREAM << "ERROR"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_ERROR_LOG
#ifdef NO_WARN_LOG
	#define WARN_LOG(msg)
#else
	#define WARN_LOG(msg) LOG_STREAM << __TIME__ << "(" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::hConsole, 14); \
			LOG_STREAM << "WARN"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM <<  "]  " << msg << std::endl;
#endif //NO_WARN_LOG
#ifdef NO_INFO_LOG
	#define INFO_LOG(msg)
#else
	#define INFO_LOG(msg) LOG_STREAM << __TIME__ << "(" << __func__ << ":" << __LINE__ << ") - [INFO]  " << msg << std::endl;
#endif //NO_INFO_LOG
#ifdef NO_DEBUG_LOG
	#define DEBUG_LOG(msg)
#else
	#define DEBUG_LOG(msg) LOG_STREAM << __TIME__ << "(" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::hConsole, 11); \
			LOG_STREAM << "DEBUG"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_DEBUG_LOG
#ifdef NO_TRACE_LOG
	#define TRACE_LOG(msg)
#else
	#define TRACE_LOG(msg) LOG_STREAM << __TIME__ << "(" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::hConsole, 7); \
			LOG_STREAM << "TRACE"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_TRACE_LOG

#else //LOGGER_NOT_VERBOSE

#ifdef NO_FATAL_LOG
#define FATAL_LOG(msg)
#else
	#define FATAL_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::hConsole, 13); \
			LOG_STREAM << "F"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_FATAL_LOG
#ifdef NO_ERROR_LOG
	#define ERROR_LOG(msg)
#else
	#define ERROR_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::hConsole, 12); \
			LOG_STREAM << "E"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_ERROR_LOG
#ifdef NO_WARN_LOG
	#define WARN_LOG(msg)
#else
	#define WARN_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::hConsole, 14); \
			LOG_STREAM << "W"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_WARN_LOG
#ifdef NO_INFO_LOG
	#define INFO_LOG(msg)
#else
	#define INFO_LOG(msg) LOG_STREAM << "[I] " << msg << std::endl;
#endif //NO_INFO_LOG
#ifdef NO_DEBUG_LOG
	#define DEBUG_LOG(msg)
#else
	#define DEBUG_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::hConsole, 11); \
			LOG_STREAM << "D"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_DEBUG_LOG
#ifdef NO_TRACE_LOG
	#define TRACE_LOG(msg)
#else
	#define TRACE_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::hConsole, 7); \
			LOG_STREAM << "T"; \
			SetConsoleTextAttribute(Logger::hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_TRACE_LOG

#endif

#define LOG(level, msg) \
	switch (level) {\
		case Logger::Fatal: \
			FATAL_LOG(msg) \
			break; \
		case Logger::Error: \
			ERROR_LOG(msg) \
			break; \
		case Logger::Warn: \
			WARN_LOG(msg) \
			break; \
		case Logger::Info: \
			INFO_LOG(msg) \
			break; \
		case Logger::Debug: \
			DEBUG_LOG(msg) \
			break; \
		case Logger::Trace: \
			TRACE_LOG(msg) \
			break; \
	}
}