#ifndef MARCHINGCUBES_HPP
#define MARCHINGCUBES_HPP

#include "Raster.hpp"
#include "ExPolygon.hpp"

namespace Slic3r { namespace sla {

ExPolygons to_expolygons(const sla::Raster &raster);

}} // namespace Slic3r::sla

#endif // MARCHINGCUBES_HPP
