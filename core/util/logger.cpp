#include <header.h>

namespace dig {
	Logger* Logger::m_pThis = NULL;
	std::ofstream Logger::m_Logfile;
	
	Logger::Logger() {}
	
	Logger* Logger::get() {
		if (m_pThis == NULL) {
			m_pThis = new Logger();
			m_Logfile.open("Log.txt", std::ios_base::app);
		}
		return (m_pThis);
	}
	 
	void Logger::log(std::string msg) {
		m_Logfile << msg << '\n';
	}
}