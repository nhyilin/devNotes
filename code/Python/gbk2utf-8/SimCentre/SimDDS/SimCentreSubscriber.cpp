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
#include"staticbitoperate.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
int samples = 0;
SimCentreSubscriber::SimCentreSubscriber()
    : mp_participant(nullptr)
    , mp_subscriber(nullptr)
{
	QString logtext = "";
	QtSettingSet::instance()->readConfig("PRINT_LOG", "log", logtext);
	setlogtext(logtext.toInt());
	staticBitOperater::init();
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
		GUID_t guid = sub->getGuid();
        if (m_info.sampleKind == ALIVE)
        {
			if (m_Sim.type() == "0008")
			{
				unsigned short lowbyte = (unsigned short)m_Sim.data()[0];
				unsigned short higebyte = (unsigned short)m_Sim.data()[1];
				unsigned short receiveBuffer = (higebyte << 8) + lowbyte;

				unsigned short myMask = staticBitOperater::src2TempMask[nodename];
				if ((receiveBuffer & myMask) == myMask)//为true则发送的命令包含本节点
				{
					m_messageQueue.push(m_Sim);
					SimMessageDDs simdds;
					{
						QtSettingSet::instance()->readConfig("FEEDBACK_COR_RUN", simdds);
						simdds.time = currentDataTime().toLocal8Bit();
						simdds.count = samples++;
						////拼接数据 +step - stepnum - count;
						//std::string step = QString::number(m_step).toStdString();;
						//for (int j = 0; j < step.length(); j++)
						//{
						//	simdds.data.push_back(step[j]);
						//}
						//simdds.data.push_back('-');
						////step_num
						//std::string stepnum = QString::number(simdds.count - 10).toStdString();
						//for (int n = 0; n < stepnum.length(); n++)
						//{
						//	simdds.data.push_back(stepnum[n]);
						//}
						//simdds.data.push_back('-');
						////count;
						//std::string num = QString::number(simdds.count).toStdString();
						//for (int k = 0; k < num.length(); k++)
						//{
						//	simdds.data.push_back(num[k]);
						//}
					}
					SimDDS::instance()->SimDDSSubPublisher(simdds);
					//TerminalPubPublisherOutput(simdds);
					std::cout << "type" << simdds.type << "count " << simdds.count << endl;
				}
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
			if (blogtext)
			{
				SimpleLog::instance()->writelog(simdds);
			}
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


