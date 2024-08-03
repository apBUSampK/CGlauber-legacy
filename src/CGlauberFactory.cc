//
// Created by apbus_amp_k on 26.02.24.
//

#include "CGlauberFactory.hh"

#include "CGlauberGenerator.hh"

cola::VFilter *CGlauberFactory::create(const std::map<std::string, std::string>& paramMap) {
    return new CGlauberGenerator(paramMap.at("name_a"), paramMap.at("name_b"), std::stod(paramMap.at("energy")), std::stoi(paramMap.at("is_collider")));
}