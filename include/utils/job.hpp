#ifndef A0DA1F5D_51AD_4C72_9F6E_47FF922D6A10
#define A0DA1F5D_51AD_4C72_9F6E_47FF922D6A10

#include <filesystem>
#include <iostream>
#include <vector>

#include <mpi.h>

#include <oneapi/tbb/task_group.h>
#include "components/code.hpp"
#include "components/input.hpp"

namespace Moru
{
    class Job
    {
    public:
        int id_;
        Code code_;                         // departure
        std::vector<Input> inputs_;         // departure
        std::filesystem::path working_dir_; // destination

        MPI_Comm comm_; // job id
        MPI_Info info_;
        MPI_Status status_;
        int np_ = 1;
        std::vector<std::string> argv_;
        int message_;
        std::vector<int> errors_;

    private:
        oneapi::tbb::task_group task_;

    public:
        Job() = delete;
        Job& operator=( Job&& job )
        {
            spdlog::debug( "Job& operator=( Job&& )" );
            return *this;
        }
        Job& operator=( const Job& job )
        {
            spdlog::debug( "Job& operator=( const Job& job )" );
            return *this;
        }

        Job( const Job& job )
            : id_{ job.id_ },
              code_{ job.code_ },
              inputs_{ job.inputs_ },
              working_dir_{ job.working_dir_ },
              comm_{ job.comm_ },
              info_{ job.info_ },
              status_{ job.status_ },
              np_{ job.np_ },
              argv_{ job.argv_ },
              message_{ job.message_ },
              errors_{ job.errors_ }
        { // 만들어야함
            spdlog::debug( "Job( const Job& job )" );
        }

        Job( Job&& job )
            : id_{ job.id_ },
              code_{ job.code_ },
              inputs_{ job.inputs_ },
              working_dir_{ job.working_dir_ },
              comm_{ job.comm_ },
              info_{ job.info_ },
              status_{ job.status_ },
              np_{ job.np_ },
              argv_{ job.argv_ },
              message_{ job.message_ },
              errors_{ job.errors_ }
        {
            spdlog::debug( "Job( Job&& job)" );
        }

        Job( int id, const Code& code, const std::vector<Input>& inputs, const std::filesystem::path& working_dir )
            : id_{ id }, code_{ code }, inputs_{ inputs }
        {
            working_dir_ = std::filesystem::absolute( working_dir );
            MPI_Info_create( &info_ );
            MPI_Info_set( info_, "path", working_dir_.string().c_str() );
            MPI_Info_set( info_, "wdir", working_dir_.string().c_str() );

            if( code_.type == "space" )
            {
                argv_.push_back( "--mverse" );
                argv_.push_back( "-i" );
                for( auto input : inputs_ )
                {
                    argv_.push_back( input.file_.filename().string() );
                }
            }
            else if( code_.type == "cupid" )
            {
            }
            else
            {
            }

            errors_.resize( np_ );
        }

        void prefare()
        {
            std::filesystem::remove_all( working_dir_ );
            std::filesystem::create_directories( working_dir_ );

            std::filesystem::copy_file( code_.executable, working_dir_ / code_.executable.filename() );
            for( auto dependency : code_.dependencies )
            {
                std::filesystem::copy_file( dependency, working_dir_ / dependency.filename() );
            }
            for( auto input : inputs_ )
            {
                std::filesystem::copy_file( input.file_, working_dir_ / input.file_.filename() );
            }
        }

        void run()
        {
            std::filesystem::current_path( working_dir_ );

            auto command = code_.executable.filename();
            spdlog::info( "Working directory: {}", working_dir_.string() );

            char** argv_char_ = new char*[ argv_.size() + 1 ];
            for( int i = 0; i < argv_.size(); ++i )
            {
                argv_char_[ i ] = const_cast<char*>( argv_[ i ].c_str() );
            }
            argv_char_[ argv_.size() ] = nullptr;

            MPI_Comm_spawn( command.string().c_str(), argv_char_, np_, info_, 0, MPI_COMM_SELF, &comm_, errors_.data() );
            MPI_Recv( &message_, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, comm_, &status_ );
            MPI_Comm_disconnect( &comm_ );
            spdlog::info( "Received value {}/42 from {}", message_, comm_ );
        }
    };
} // namespace Moru
#endif /* A0DA1F5D_51AD_4C72_9F6E_47FF922D6A10 */
