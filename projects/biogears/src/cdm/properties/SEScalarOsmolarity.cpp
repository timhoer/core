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

#include <biogears/cdm/properties/SEScalarOsmolarity.h>
#include <biogears/cdm/stdafx.h>

const OsmolarityUnit OsmolarityUnit::Osm_Per_L("Osm/L");
const OsmolarityUnit OsmolarityUnit::mOsm_Per_L("mOsm/L");

CDM::ScalarOsmolarityData* SEScalarOsmolarity::Unload() const
{
  if (!IsValid())
    return nullptr;
  CDM::ScalarOsmolarityData* data(new CDM::ScalarOsmolarityData());
  SEScalarQuantity::Unload(*data);
  return data;
}

bool OsmolarityUnit::IsValidUnit(const std::string& unit)
{
  if (Osm_Per_L.GetString().compare(unit) == 0)
    return true;
  if (mOsm_Per_L.GetString().compare(unit) == 0)
    return true;
  return false;
}

const OsmolarityUnit& OsmolarityUnit::GetCompoundUnit(const std::string& unit)
{
  if (Osm_Per_L.GetString().compare(unit) == 0)
    return Osm_Per_L;
  if (mOsm_Per_L.GetString().compare(unit) == 0)
    return mOsm_Per_L;
  std::stringstream err;
  err << unit << " is not a valid Osmolarity unit";
  throw CommonDataModelException(err.str());
}