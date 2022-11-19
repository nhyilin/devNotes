//
// Created by 裴奕霖 on 2022/11/18.
//

#ifndef REFACTORING_SRC_STDAFX_H_
#define REFACTORING_SRC_STDAFX_H_
#include "param_deliver.h"
#include <QObject>
#include <QThread>
#include <QWidget>
#include <QWindow>
#include <iostream>
#include <string>
#include <QDebug>
#include <QCoreApplication>
#include "BoostLog/InitLog.h"
#include "BoostLog/ParseINI.h"
#include <QApplication>

#include <boost/filesystem.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/detail/format.hpp>
#include <boost/log/detail/thread_id.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>


#endif  // REFACTORING_SRC_STDAFX_H_
