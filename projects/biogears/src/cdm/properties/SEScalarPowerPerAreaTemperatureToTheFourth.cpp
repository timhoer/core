/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include <biogears/cdm/properties/SEScalarPowerPerAreaTemperatureToTheFourth.h>
#include <biogears/cdm/stdafx.h>

const PowerPerAreaTemperatureToTheFourthUnit PowerPerAreaTemperatureToTheFourthUnit::W_Per_m2_K4("W/ m^2 K^4");

CDM::ScalarPowerPerAreaTemperatureToTheFourthData* SEScalarPowerPerAreaTemperatureToTheFourth::Unload() const
{
  if (!IsValid()) {
    return nullptr;
  }
  CDM::ScalarPowerPerAreaTemperatureToTheFourthData* data(new CDM::ScalarPowerPerAreaTemperatureToTheFourthData());
  SEScalarQuantity::Unload(*data);
  return data;
}

bool PowerPerAreaTemperatureToTheFourthUnit::IsValidUnit(const std::string& unit)
{
  if (W_Per_m2_K4.GetString().compare(unit) == 0) {
    return true;
  }
  return false;
}

const PowerPerAreaTemperatureToTheFourthUnit& PowerPerAreaTemperatureToTheFourthUnit::GetCompoundUnit(const std::string& unit)
{
  if (W_Per_m2_K4.GetString().compare(unit) == 0) {
    return W_Per_m2_K4;
  }
  std::stringstream err;
  err << unit << " is not a valid PowerPerAreaTemperatureToTheFourth unit";
  throw CommonDataModelException(err.str());
}