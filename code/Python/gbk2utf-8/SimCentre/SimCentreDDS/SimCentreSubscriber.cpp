// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file SimCentreSubscriber.cpp
 *
 */

#include "SimCentreSubscriber.h"
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/Domain.h>
#include "simdds.h"
#include "SimMessageDDs.h"
#include "simplelog.h"
#include "qtsettingset.h"
#include "SimDataAnalysis.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "MyPubCallbackSubscriber.h"

#include "feedbackcorrunArrayTimer.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
void Callback(void(*perfect)(SimMessageDDs), SimMessageDDs dds)
{
	perfect(dds);
}

SimCentreSubscriber::SimCentreSubscriber()
    : mp_participant(nullptr)
    , mp_subscriber(nullptr)
{
	QString logtext = "";
	QtSettingSet::instance()->readConfig("PRINT_LOG", "log", logtext);
	setlogtext(logtext.toInt());
	FeedBackcorrunArrayTimer::init();
}

bool SimCentreSubscriber::init(std::string TopName)
{
    ParticipantAttributes PParam;
    PParam.rtps.builtin.discovery_config.discoveryProtocol = DiscoveryProtocol_t::SIMPLE;
    PParam.rtps.builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
    PParam.rtps.builtin.discovery_config.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    PParam.rtps.builtin.discovery_config.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    PParam.rtps.builtin.discovery_config.leaseDuration = c_TimeInfinite;
    PParam.rtps.setName("Participant_sub");
    mp_participant = Domain::createParticipant(PParam);
    if (mp_participant == nullptr)
    {
        return false;
    }

    //REGISTER THE TYPE

    Domain::registerType(mp_participant, &m_type);
    //CREATE THE SUBSCRIBER
    SubscriberAttributes Rparam;
    Rparam.topic.topicKind = NO_KEY;
    Rparam.topic.topicDataType = "SimMessage";
    Rparam.topic.topicName = /*"SimMessageTopic"*/TopName;
    Rparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
    Rparam.topic.historyQos.depth = 30;
    Rparam.topic.resourceLimitsQos.max_samples = 50;
    Rparam.topic.resourceLimitsQos.allocated_samples = 50;
    Rparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS;
    Rparam.qos.m_durability.kind = TRANSIENT_LOCAL_DURABILITY_QOS;
    mp_subscriber = Domain::createSubscriber(mp_participant, Rparam, (SubscriberListener*)&m_listener);

    if (mp_subscriber == nullptr)
    {
        return false;
    }


    return true;
}

SimCentreSubscriber::~SimCentreSubscriber()
{
    // TODO Auto-generated destructor stub
    Domain::removeParticipant(mp_participant);
}

void SimCentreSubscriber::SubListener::onSubscriptionMatched(
        Subscriber* /*sub*/,
        MatchingInfo& info)
{
    if (info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Subscriber matched" << std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Subscriber unmatched" << std::endl;
    }
}

void SimCentreSubscriber::SubListener::onNewDataMessage(
        Subscriber* sub)
{
    if (sub->takeNextData((void*)&m_Sim, &m_info))
    {
		//GUID_t guid = sub->getGuid();
        if (m_info.sampleKind == ALIVE)
        {
		
			if (m_Sim.type() == "0007")
			{
				FeedBackcorrunArrayTimer::on_nodeReceiveMessage(m_Sim.src(), m_Sim.data());
				//FeedBackcorrunArrayTimer::on_nodeReceiveMessage(m_Sim.src(),m_Sim.data());
				//mutex_.unlock();
				return;
			}
            mutex_.lock();
			simdds.tastID = m_Sim.tastID();
			simdds.src = m_Sim.src();
			simdds.dest = m_Sim.dest();
			simdds.time = m_Sim.time();
			simdds.step = m_Sim.step();
			simdds.type = m_Sim.type();
			simdds.subtype = m_Sim.subtype();
			simdds.count = m_Sim.count();
			simdds.data = m_Sim.data();
			/*simView simview;
			simview.src = m_Sim.src();
			simview.time = currentDataTime().toStdString();
			simview.count = m_Sim.count();
			vesim.push_back(simview);
			if (vesim.size() > 20000)
			{
				static uint32_t sample = 0;
				int nCount = simdds.data.size();
				QString strPath = QApplication::applicationDirPath();
				QString filename = currentData() + "-log100dds.txt";
				QFile file(strPath + "/" + filename);
				if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
					return;
				QTextStream out(&file);
				for (int i = 0; i < vesim.size(); i++)
				{
					out << "src" << QString(vesim.at(i).src.c_str()) << " "
						<< "time" << QString(vesim.at(i).time.c_str()) << " "
						<< "count" << vesim.at(i).count << "\n\r";
				}
				file.close();
			}*/
			////if (blogtext)
			////{
			////	SimpleLog::instance()->writelog(simdds);
			////}
			//if (simdds.type == "0007")
			//{
			//	std::stringstream stream;
			//	for (int i = 0; i < simdds.data.size(); i++)
			//	{
			//		stream << simdds.data.at(i);
			//	}
			//	std::string ss;
			//	stream >> ss;
			//	QString temp = QString::fromLocal8Bit(ss.c_str());
			//	mapset.SetMapData(simdds.src, temp.toStdString());
			//}
			Callback(SubscriberCallback, simdds);
			mutex_.unlock();
		}
    }

}


void SimCentreSubscriber::run()
{
    std::cout << "Subscriber running. Please press enter to stop the Subscriber" << std::endl;
   // std::cin.ignore();
}


void SimCentreSubscriber::run(
        uint32_t number)
{
    std::cout << "Subscriber running until " << number << "samples have been received" << std::endl;
    while (number > this->m_listener.n_samples)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}