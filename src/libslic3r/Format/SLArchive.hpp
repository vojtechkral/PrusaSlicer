#ifndef SLARCHIVE_HPP
#define SLARCHIVE_HPP

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "libslic3r/TriangleMesh.hpp"
#include "libslic3r/PrintConfig.hpp"
#include "libslic3r/ExPolygon.hpp"

namespace Slic3r {

class SLArchiveReaderBase {
public:
    
    virtual ~SLArchiveReaderBase();
    virtual DynamicPrintConfig read_config() = 0;
    virtual std::vector<ExPolygons> read_layers() = 0;
};

class SL1ArchiveReader: public SLArchiveReaderBase {
    struct Impl;
    std::unique_ptr<Impl> m_archive_data;
    
public:
    SL1ArchiveReader(const char *archive_filename);
    ~SL1ArchiveReader() override;
    
    SL1ArchiveReader(const SL1ArchiveReader&);
    SL1ArchiveReader(SL1ArchiveReader&&);
    
    SL1ArchiveReader& operator=(const SL1ArchiveReader&);
    SL1ArchiveReader& operator=(SL1ArchiveReader&&);
    
    DynamicPrintConfig read_config() override;
    std::vector<ExPolygons> read_layers() override;
};

TriangleMesh load_sla_archive(SLArchiveReaderBase &reader, DynamicPrintConfig &cfg);

} // namespace Slic3r

#endif // SLARCHIVE_HPP
