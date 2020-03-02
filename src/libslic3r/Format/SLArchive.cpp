#include "SLArchive.hpp"
#include "SLA/RasterToPolygon.hpp"
#include <boost/filesystem.hpp>

#include "miniz_extension.hpp"

namespace Slic3r {

SLArchiveReaderBase::~SLArchiveReaderBase() = default;

TriangleMesh load_sla_archive(SLArchiveReaderBase &reader, DynamicPrintConfig &cfg)
{
    
    return {};
}

struct SL1ArchiveReader::Impl {
    mz_zip_archive arch;
};

SL1ArchiveReader::SL1ArchiveReader(const char *path)
    : m_archive_data(new Impl{})
{
    if (! open_zip_reader(&m_archive_data->arch, path))
        throw std::runtime_error(std::string("Unable to init zip reader for ") + path);
    
    auto *arch = &m_archive_data->arch;
    mz_uint num_entries = mz_zip_reader_get_num_files(arch);
    
    for (mz_uint i = 0; i < num_entries; ++i) {
        mz_zip_archive_file_stat stat;
        
        if (mz_zip_reader_file_stat(arch, i, &stat)) {
            boost::filesystem::path entrypath(stat.m_filename);
            std::string ext(entrypath.extension().string());
            for (char &c : ext) c = char(std::tolower(c));
            
            if (ext == "png") {
                mz_bool res = mz_zip_reader_extract_file_to_mem(&arch, stat.m_filename, (void*)buffer.data(), (size_t)stat.m_uncomp_size, 0);    
                
            }
//            stat.m_filename;
        }
    }
}

SL1ArchiveReader::~SL1ArchiveReader()
{
    close_zip_reader(&m_archive_data->arch);
}

SL1ArchiveReader::SL1ArchiveReader(const SL1ArchiveReader &other)
    : m_archive_data(new Impl{*other.m_archive_data})
{}

SL1ArchiveReader& SL1ArchiveReader::operator=(const SL1ArchiveReader &other)
{
    m_archive_data.reset(new Impl{*other.m_archive_data});
    return *this;
}

SL1ArchiveReader::SL1ArchiveReader(SL1ArchiveReader &&o): m_archive_data(std::move(o.m_archive_data)) {}
SL1ArchiveReader& SL1ArchiveReader::operator=(SL1ArchiveReader &&o)
{
    m_archive_data = std::move(o.m_archive_data);
    return *this;
}

DynamicPrintConfig SL1ArchiveReader::read_config()
{
    return {};
}

std::vector<ExPolygons> SL1ArchiveReader::read_layers()
{
    return {};
}

}
