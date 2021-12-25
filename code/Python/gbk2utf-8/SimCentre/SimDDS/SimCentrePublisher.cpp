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
 * @file SimCentrePublisher.cpp
 *
 */

#include "SimCentrePublisher.h"
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/Domain.h>

#include <thread>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

SimCentrePublisher::SimCentrePublisher()
    : mp_participant(nullptr)
    , mp_publisher(nullptr)
{
}

bool SimCentrePublisher::init(std::string TopName)
{
    ParticipantAttributes PParam;
    PParam.rtps.builtin.discovery_config.discoveryProtocol = DiscoveryProtocol_t::SIMPLE;
    PParam.rtps.builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
    PParam.rtps.builtin.discovery_config.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    PParam.rtps.builtin.discovery_config.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;
    PParam.rtps.builtin.discovery_config.leaseDuration = c_TimeInfinite;
    PParam.rtps.setName("Participant_pub");
    mp_participant = Domain::createParticipant(PParam);

    if (mp_participant == nullptr)
    {
        return false;
    }
    //REGISTER THE TYPE

    Domain::registerType(mp_participant, &m_subtype);
    //CREATE THE PUBLISHER
    PublisherAttributes Wparam;
    Wparam.topic.topicKind = NO_KEY;
    Wparam.topic.topicDataType = "SimMessage";
    Wparam.topic.topicName = /*"SimMessageTopic"*/TopName;
    Wparam.topic.historyQos.kind = KEEP_LAST_HISTORY_QOS;
    Wparam.topic.historyQos.depth = 30;
    Wparam.topic.resourceLimitsQos.max_samples = 50;
    Wparam.topic.resourceLimitsQos.allocated_samples = 50;
    Wparam.times.heartbeatPeriod.seconds = 2;
    Wparam.times.heartbeatPeriod.nanosec = 200 * 1000 * 1000;
    Wparam.qos.m_reliability.kind = RELIABLE_RELIABILITY_QOS;
	Wparam.qos.m_publishMode.kind = ASYNCHRONOUS_PUBLISH_MODE;
    mp_publisher = Domain::createPublisher(mp_participant, Wparam, (PublisherListener*)&m_listener);
    if (mp_publisher == nullptr)
    {
        return false;
    }

    return true;

}

SimCentrePublisher::~SimCentrePublisher()
{
    // TODO Auto-generated destructor stub
    Domain::removeParticipant(mp_participant);
}

void SimCentrePublisher::PubListener::onPublicationMatched(
        Publisher* /*pub*/,
        MatchingInfo& info)
{
    if (info.status == MATCHED_MATCHING)
    {
        n_matched++;
        firstConnected = true;
        std::cout << "Publisher matched" << std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Publisher unmatched" << std::endl;
    }
}

void SimCentrePublisher::runThread(
        uint32_t samples,
        uint32_t sleep)
{
	//if (MIddleByValueSet::instance()->getpublishpause()){ return ;}
    //if (samples == 0)
    //{
    //    while (!stop)
    //    {
    //        if (publish(/*false*/))
    //        {
				//std::cout << "TastID" << m_Sim.tastID() << " "
				//	<< "src" << m_Sim.src() << " "
				//	<< "dest" << m_Sim.dest() << " "
				//	<< "time" << m_Sim.time() << " "
				//	<< "type" << m_Sim.type() << " "
				//	<< "subtype" << m_Sim.subtype() << " "
				//	<< "count" << m_Sim.count() << " "
				//	<< std::endl;
    //        }
    //        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    //    }
    //}
    //else
    //{
    //    for (uint32_t i = 0; i < samples; ++i)
    //    {
    //        if (!publish())
    //        {
    //            --i;
    //        }
    //        else
    //        {
				//std::cout << "TastID" << m_Sim.tastID() << " "
				//	<< "src" << m_Sim.src() << " "
				//	<< "dest" << m_Sim.dest() << " "
				//	<< "time" << m_Sim.time() << " "
				//	<< "type" << m_Sim.type() << " "
				//	<< "subtype" << m_Sim.subtype() << " "
				//	<< "count" << m_Sim.count() << " "
				//	<< std::endl;
    //        }
    //        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    //    }
    //}
}

void SimCentrePublisher::run(
        uint32_t samples,
        uint32_t sleep)
{
    stop = false;
    std::thread thread(&SimCentrePublisher::runThread, this, samples, sleep);
    if (samples == 0)
    {
        std::cout << "Publisher running. Please press enter to stop the Publisher at any time." << std::endl;
        std::cin.ignore();
        stop = true;
    }
    else
    {
        std::cout << "Publisher running " << samples << " samples." << std::endl;
    }
    thread.join();
}

bool SimCentrePublisher::publish(
        bool waitForListener)
{
    if (m_listener.firstConnected || !waitForListener || m_listener.n_matched > 0)
    {
		m_Sim.tastID("任务1");
		m_Sim.src("信源");
		m_Sim.dest("信宿");
		m_Sim.time("时间戳");
		m_Sim.step("步长");
		m_Sim.type("指令类");
		m_Sim.subtype("子类型");
		m_Sim.count(m_Sim.count() + 1);
		mp_publisher->write((void*)&m_Sim);
        return true;
    }
    return false;
}


bool SimCentrePublisher::publish(SimMessageDDs simdds, bool waitForListener)
{
	if (m_listener.firstConnected || !waitForListener || m_listener.n_matched > 0)
	{
		m_Sim.tastID(simdds.tastID);
		m_Sim.src(simdds.src);
		m_Sim.dest(simdds.dest);
		m_Sim.time(simdds.time);
        m_Sim.step(simdds.step);
		m_Sim.type(simdds.type);
		m_Sim.subtype(simdds.subtype);
		m_Sim.count(simdds.count);
		m_Sim.data(simdds.data);
		mp_publisher->write((void*)&m_Sim);
		return true;
	}
	return false;
}