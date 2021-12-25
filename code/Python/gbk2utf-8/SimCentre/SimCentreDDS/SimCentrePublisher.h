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
 * @file SimCentrePublisher.h
 *
 */

#ifndef SimCentrePublisher_h__
#define SimCentrePublisher_h__

#include "SimCentrePubSubTypes.h"
#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/publisher/PublisherListener.h>


#include "SimMessage.h"
#include "SimMessageDDs.h"

class SimCentrePublisher {
public:
	SimCentrePublisher();
	virtual ~SimCentrePublisher();
	//!Initialize
	bool init(std::string TopName);
	//!Publish a sample
	bool publish(bool waitForListener = true);
	//!Publish a sample back
	bool publish(SimMessageDDs simdds, bool waitForListener = true);
	//!Run for number samples
	void run(uint32_t number, uint32_t sleep);
public:
	SimMessage m_Sim;
	eprosima::fastrtps::Participant* mp_participant;
	eprosima::fastrtps::Publisher* mp_publisher;
	bool stop;
	class PubListener:public eprosima::fastrtps::PublisherListener
	{
	public:
		PubListener():n_matched(0),firstConnected(false){};
		~PubListener(){};
		void onPublicationMatched(eprosima::fastrtps::Publisher* pub, eprosima::fastrtps::rtps::MatchingInfo& info);
		int n_matched;
        bool firstConnected;
	}m_listener;
	void runThread(uint32_t number, uint32_t sleep);
	SimCentrePubSubType m_subtype;
};



#endif // SimCentrePublisher_h__
