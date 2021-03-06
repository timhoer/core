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

#include <biogears/cdm/properties/SEScalarEnergy.h>
#include <biogears/cdm/stdafx.h>

const EnergyUnit EnergyUnit::J("J");
const EnergyUnit EnergyUnit::mJ("mJ");
const EnergyUnit EnergyUnit::kJ("kJ");
const EnergyUnit EnergyUnit::kcal("kcal");

CDM::ScalarEnergyData* SEScalarEnergy::Unload() const
{
  if (!IsValid())
    return nullptr;
  CDM::ScalarEnergyData* data(new CDM::ScalarEnergyData());
  SEScalarQuantity::Unload(*data);
  return data;
}

bool EnergyUnit::IsValidUnit(const std::string& unit)
{
  if (J.GetString().compare(unit) == 0)
    return true;
  if (mJ.GetString().compare(unit) == 0)
    return true;
  if (kJ.GetString().compare(unit) == 0)
    return true;
  if (kcal.GetString().compare(unit) == 0)
    return true;
  return false;
}

const EnergyUnit& EnergyUnit::GetCompoundUnit(const std::string& unit)
{
  if (J.GetString().compare(unit) == 0)
    return J;
  if (mJ.GetString().compare(unit) == 0)
    return mJ;
  if (kJ.GetString().compare(unit) == 0)
    return kJ;
  if (kcal.GetString().compare(unit) == 0)
    return kcal;
  std::stringstream err;
  err << unit << " is not a valid Energy unit";
  throw CommonDataModelException(err.str());
}