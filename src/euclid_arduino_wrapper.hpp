/******************************************************************************
Copyright (c) 2016, Intel Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef __ARDUINO_WRAPPER_
#define __ARDUINO_WRAPPER_
#include <nodelet/nodelet.h>
#include <boost/version.hpp>
#if ((BOOST_VERSION / 100) % 1000) >= 53
#include <boost/thread/lock_guard.hpp>
#endif
#include <boost/thread.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <euclid_arduino_wrapper/EuclidArduinoWrapperConfig.h>
    
namespace euclid_arduino_wrapper {
    class EuclidArduinoWrapper : public nodelet::Nodelet {
    
        boost::shared_ptr<image_transport::ImageTransport> it_;
        image_transport::Subscriber sub_depth_;

        int queue_size_;
        int roi_x;
        int roi_y;
        int roi_width;
        int roi_height;

        boost::mutex connect_mutex_;
        image_transport::Publisher pub_arduino_;
        dynamic_reconfigure::Server<euclid_arduino_wrapper::EuclidArduinoWrapperConfig> server;
        boost::shared_ptr<dynamic_reconfigure::Server<euclid_arduino_wrapper::EuclidArduinoWrapperConfig> > dynamic_reconf_server_;
        dynamic_reconfigure::Server<euclid_arduino_wrapper::EuclidArduinoWrapperConfig>::CallbackType f;
        



        public:
            virtual void onInit();
            void connectCb();
            
            void dynamicConfigureServerCallback(euclid_arduino_wrapper::EuclidArduinoWrapperConfig &config, uint32_t level);

            void imageCb(const sensor_msgs::ImageConstPtr& image_msg);
    
    };

}

#endif
