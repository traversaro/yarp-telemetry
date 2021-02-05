/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */


#include <yarp/os/Time.h>
#include <yarp/os/Network.h>
#include <yarp/telemetry/BufferManager.h>

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace yarp::os;

constexpr size_t n_samples{20};
constexpr size_t threshold{10};
constexpr double check_period{1.0};



int main()
{
    Network yarp;
    yarp::telemetry::BufferConfig bufferConfig;

    // we configure our API to use our periodic saving option 
    bufferConfig.n_samples = n_samples;
    bufferConfig.save_period = check_period;
    bufferConfig.data_threshold = threshold;
    bufferConfig.save_periodically = true;
    std::vector<yarp::telemetry::ChannelInfo> vars{ { "one",{2,3} },
                                                    { "two",{3,2} } };
    bufferConfig.channels = vars;

    nlohmann::json j = bufferConfig;

    std::cout << "Here is the resulting json file "<<std::endl;
    std::cout << j << std::endl;

    yarp::telemetry::BufferManager<int32_t> bm;

    auto ok = bm.configureFromFile("test_json.json");

    if (!ok) {
        std::cout << "Problems configuring from file" << std::endl;
        return 1;
    }

    std::cout << "Starting loop" << std::endl;
    for (int i = 0; i < 40; i++) {
        bm.push_back({ i }, "one");
        yarp::os::Time::delay(0.01);
        bm.push_back({ i + 1 }, "two");
    }

    yarp::os::Time::delay(3.0);
    return 0;
 }
