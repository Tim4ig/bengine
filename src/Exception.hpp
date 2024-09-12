
#pragma once

#include <stdexcept>
#include <string>
#include <stacktrace>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define THROW(message) { throw be::exception::Exception(be::exception::AssembleMessage(message, __FUNCTION__, __LINE__, be::exception::GetStackTrace())); }
#define TIF ;{ if(FAILED(hr)) THROW("Hresult was: " + std::to_string(hr)); }

namespace be::exception
{
	inline std::string GetStackTrace()
	{
		auto trace = std::stacktrace::current();
		std::string traceString;

		for (auto& frame : trace)
		{
			if (frame == trace[0]) continue;
			traceString += "\n\t" + frame.description();
		}

		return traceString;
	}

	inline std::string AssembleMessage(std::string msg, std::string function, int line, std::string trace)
	{
		std::string message = "";
		message += "\n----------------------------------------------------------------";
		message += "\nAn exception has occurred!";
		message += "\nMessage: " + msg;
		message += "\nIn function: " + function;
		message += "\nOn line: " + std::to_string(line);
		message += "\nStack trace:" + trace;
		message += "\n----------------------------------------------------------------";
		message += "\n\n";

		return message;
	}

	inline std::exception Exception(std::string message)
	{
		OutputDebugStringA(message.c_str());
		return std::runtime_error(message);
	}
}
