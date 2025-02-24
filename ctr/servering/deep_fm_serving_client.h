/*
 * deep_fm_serving_client.h
 *
 *  Created on: 2018年2月7日
 *      Author: JerryCat
 */

#ifndef DEEP_FM_SERVING_CLIENT_H_
#define DEEP_FM_SERVING_CLIENT_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "grpc++/create_channel.h"
#include "grpc++/security/credentials.h"
#include "tensorflow_serving/apis/prediction_service.grpc.pb.h"

using tensorflow::serving::PredictionService;

class ServingClient
{
public:
    static std::shared_ptr<ServingClient> createClient(const std::string sServerPort){
        std::shared_ptr<ServingClient> p = std::make_shared<ServingClient>(grpc::CreateChannel(sServerPort, grpc::InsecureChannelCredentials()));
        return p;
    }
public:
    ServingClient(const std::shared_ptr<grpc::Channel>& channel) : _stub(PredictionService::NewStub(channel)) { }
    int callPredict(const std::string& model_name, const std::string& model_signature_name, std::map<std::string, std::string> & result);

private:
    std::unique_ptr<PredictionService::Stub>    _stub;
};


#endif /* DEEP_FM_SERVING_CLIENT_H_ */
