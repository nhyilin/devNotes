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
 * @file SimCentreSubscriber.h
 *
 */
#ifndef SimCentreSubscriber_h__
#define SimCentreSubscriber_h__
#include "SimCentrePubSubTypes.h"
#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include "SimMessage.h"
#include "SimMessageDDs.h"
#include "MapSet.h"
#include <mutex>

class SimCentreSubscriber
{
public:

    SimCentreSubscriber();
    virtual ~SimCentreSubscriber();
    //!Initialize the subscriber
    bool init(std::string TopName);
    //!RUN the subscriber
    void run();
    //!Run the subscriber until number samples have been received.
    void run(
            uint32_t number);	
	SimMessageDDs getsimdata() { return m_listener.getsimdata(); }
	MapSet & getmap() { return m_listener.getmapset(); }
	queue<SimMessage>& getsimQueue() { return m_listener.getqueue(); }

	void setnodename(std::string strnodename) { m_listener.nodename = strnodename; }
	void setlogtext(bool log) { m_listener.blogtext = log; }
private:

    eprosima::fastrtps::Participant* mp_participant;
    eprosima::fastrtps::Subscriber* mp_subscriber;
public:

    class SubListener : public eprosima::fastrtps::SubscriberListener
    {
    public:

        SubListener()
            : n_matched(0)
            , n_samples(0)
			, blogtext(false)
			, nodename("")
        {
        }

        ~SubListener()
        {
        }

        void onSubscriptionMatched(
                eprosima::fastrtps::Subscriber* sub,
                eprosima::fastrtps::rtps::MatchingInfo& info);
        void onNewDataMessage(
                eprosima::fastrtps::Subscriber* sub);
		SimMessageDDs getsimdata() { 
			std::lock_guard<std::mutex> lock(mutex_);
			return simdds;
		}
		MapSet& getmapset() { return mapset; }
		queue<SimMessage>& getqueue() { return m_messageQueue; }

        SimMessage m_Sim;
		queue<SimMessage> m_messageQueue;
        eprosima::fastrtps::SampleInfo_t m_info;
        int n_matched;
		std::string nodename;
        uint32_t n_samples;
		std::mutex mutex_;
		bool blogtext;
		SimMessageDDs simdds;
		MapSet mapset;
		mutex m_messageMuex;
    }
    m_listener;

private:

    SimCentrePubSubType m_type;
	SimMessageDDs    m_sim;
};

#endif // SimCentreSubscriber_h__
