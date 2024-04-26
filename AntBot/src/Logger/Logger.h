#pragma once

#include <Windows.h>
#include <fstream>
#include <chrono>

#define LOGGER_VERBOSE

#ifndef LOG_STREAM
#define LOG_STREAM Logger::getInstance().outFileStream
#endif

class Logger {
private:
	static Logger& instance() {
		static Logger instance;

		return instance;
	}

	Logger()
	{
		outFileStream = std::ofstream();
		outFileStream.open("./Debug.log");
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	~Logger()
	{
		outFileStream.close();
	}

public:
	std::ofstream outFileStream;
	HANDLE hConsole;

	static Logger& getInstance()
	{
		static std::once_flag flag;
		std::call_once(flag, [] { instance(); });
		return instance();
	}

	enum LogLevel {
		Fatal,
		Error,
		Warn,
		Info,
		Debug,
		Trace
	};
};

#ifdef LOGGER_VERBOSE

#ifdef NO_FATAL_LOG
	#define FATAL_LOG(msg)
#else
	#define FATAL_LOG(msg) LOG_STREAM << std::chrono::system_clock::now() << " (" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 13); \
			LOG_STREAM << "FATAL"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_FATAL_LOG
#ifdef NO_ERROR_LOG
	#define ERROR_LOG(msg)
#else
	#define ERROR_LOG(msg) LOG_STREAM << std::chrono::system_clock::now() << " (" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 12); \
			LOG_STREAM << "ERROR"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_ERROR_LOG
#ifdef NO_WARN_LOG
	#define WARN_LOG(msg)
#else
	#define WARN_LOG(msg) LOG_STREAM << std::chrono::system_clock::now() << " (" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 14); \
			LOG_STREAM << "WARN"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM <<  "]  " << msg << std::endl;
#endif //NO_WARN_LOG
#ifdef NO_INFO_LOG
	#define INFO_LOG(msg)
#else
	#define INFO_LOG(msg) LOG_STREAM << std::chrono::system_clock::now() << " (" << __func__ << ":" << __LINE__ << ") - [INFO]  " << msg << std::endl;
#endif //NO_INFO_LOG
#ifdef NO_DEBUG_LOG
	#define DEBUG_LOG(msg)
#else
	#define DEBUG_LOG(msg) LOG_STREAM << std::chrono::system_clock::now() << " (" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 11); \
			LOG_STREAM << "DEBUG"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_DEBUG_LOG
#ifdef NO_TRACE_LOG
	#define TRACE_LOG(msg)
#else
	#define TRACE_LOG(msg) LOG_STREAM << std::chrono::system_clock::now() << " (" << __func__ << ":" << __LINE__ << ") - ["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 7); \
			LOG_STREAM << "TRACE"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM <<  "] " << msg << std::endl;
#endif //NO_TRACE_LOG

#else //LOGGER_NOT_VERBOSE

#ifdef NO_FATAL_LOG
#define FATAL_LOG(msg)
#else
	#define FATAL_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 13); \
			LOG_STREAM << "F"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_FATAL_LOG
#ifdef NO_ERROR_LOG
	#define ERROR_LOG(msg)
#else
	#define ERROR_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 12); \
			LOG_STREAM << "E"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_ERROR_LOG
#ifdef NO_WARN_LOG
	#define WARN_LOG(msg)
#else
	#define WARN_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 14); \
			LOG_STREAM << "W"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
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
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 11); \
			LOG_STREAM << "D"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
			LOG_STREAM << "] " << msg << std::endl;
#endif //NO_DEBUG_LOG
#ifdef NO_TRACE_LOG
	#define TRACE_LOG(msg)
#else
	#define TRACE_LOG(msg) LOG_STREAM << "["; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 7); \
			LOG_STREAM << "T"; \
			SetConsoleTextAttribute(Logger::getInstance().hConsole, 15); \
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