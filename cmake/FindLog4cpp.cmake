FIND_PATH(LOG4CPP_INCLUDE_DIR 
	NAMES 
	AbortAppender.hh
	Appender.hh
	AppendersFactory.hh
	AppenderSkeleton.hh
	BasicConfigurator.hh
	BasicLayout.hh
	BufferingAppender.hh
	Category.hh
	CategoryStream.hh
	Configurator.hh
	DailyRollingFileAppender.hh
	Export.hh
	FactoryParams.hh
	FileAppender.hh
	Filter.hh
	FixedContextCategory.hh
	HierarchyMaintainer.hh
	IdsaAppender.hh
	LayoutAppender.hh
	Layout.hh
	LayoutsFactory.hh
	LevelEvaluator.hh
	LoggingEvent.hh
	Manipulator.hh
	NDC.hh
	NTEventLogAppender.hh
	OstreamAppender.hh
	PassThroughLayout.hh
	PatternLayout.hh
	Portability.hh
	Priority.hh
	PropertyConfigurator.hh
	RemoteSyslogAppender.hh
	RollingFileAppender.hh
	SimpleConfigurator.hh
	SimpleLayout.hh
	StringQueueAppender.hh
	SyslogAppender.hh
	TimeStamp.hh
	TriggeringEventEvaluatorFactory.hh
	TriggeringEventEvaluator.hh
	Win32DebugAppender.hh
	HINTS /usr/include/
	PATH_SUFFIXES log4cpp
	)

find_library(LOG4CPP_LIBRARY NAMES log4cpp log4cxx
	HINTS /usr/lib/x86_64-linux-gnu
	)

set (LOG4CPP_LIBRARY ${LOG4CPP_LIBRARY})
set (LOG4CPP_INCLUDE_DIR ${LOG4CPP_INCLUDE_DIR})

if (${LOG4CPP_INCLUDE_DIR} MATCHES "log4cpp")
	message(STATUS "Found ${LOG4CPP_INCLUDE_DIR}")
else()
	#set(LOG4CPP_INCLUDE_DIR NONE)
	message(STATUS "log4cpp include dir NOT found!")
endif()

if(${LOG4CPP_LIBRARY} MATCHES ".so" )
	message(STATUS "Found ${LOG4CPP_LIBRARY}")
else()
	#set(LOG4CPP_LIBRARY NONE)
	message(STATUS "log4cpp library NOT found!")
endif()
	

