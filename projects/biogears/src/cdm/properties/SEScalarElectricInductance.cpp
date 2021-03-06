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

#include <biogears/cdm/properties/SEScalarElectricInductance.h>
#include <biogears/cdm/stdafx.h>

const ElectricInductanceUnit ElectricInductanceUnit::H("H");

CDM::ScalarElectricInductanceData* SEScalarElectricInductance::Unload() const
{
  if (!IsValid())
    return nullptr;
  CDM::ScalarElectricInductanceData* data(new CDM::ScalarElectricInductanceData());
  SEScalarQuantity::Unload(*data);
  return data;
}

bool ElectricInductanceUnit::IsValidUnit(const std::string& unit)
{
  if (H.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricInductanceUnit& ElectricInductanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (H.GetString().compare(unit) == 0)
    return H;
  std::stringstream err;
  err << unit << " is not a valid ElectricInductance unit";
  throw CommonDataModelException(err.str());
}