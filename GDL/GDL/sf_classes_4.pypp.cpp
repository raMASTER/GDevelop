#ifdef PYSUPPORT
// This file has been generated by Py++.

#include "boost/python.hpp"
#include "c:/libs/sfml/include/sfml/system.hpp"
#include "c:/libs/sfml/include/sfml/window.hpp"
#include "c:/libs/sfml/include/sfml/window/contextsettings.hpp"
#include "c:/libs/sfml/include/sfml/graphics.hpp"
#include "c:/libs/sfml/include/sfml/audio.hpp"
#include "sf_classes_4.pypp.hpp"

namespace bp = boost::python;

void register_classes_4(){

    { //::sf::Lock
        typedef bp::class_< sf::Lock, boost::noncopyable > Lock_exposer_t;
        Lock_exposer_t Lock_exposer = Lock_exposer_t( "Lock", bp::init< sf::Mutex & >(( bp::arg("mutex") )) );
        bp::scope Lock_scope( Lock_exposer );
        bp::implicitly_convertible< sf::Mutex &, sf::Lock >();
    }

    bp::class_< sf::Matrix3 >( "Matrix3", bp::init< >() )
        .def( bp::init< float, float, float, float, float, float, float, float, float >(( bp::arg("a00"), bp::arg("a01"), bp::arg("a02"), bp::arg("a10"), bp::arg("a11"), bp::arg("a12"), bp::arg("a20"), bp::arg("a21"), bp::arg("a22") )) )
        /*.def(
            "Get4x4Elements"
            , (float const * ( ::sf::Matrix3::* )(  ) const)( &::sf::Matrix3::Get4x4Elements )
            , bp::return_internal_reference< >() )*/
        .def(
            "GetInverse"
            , (::sf::Matrix3 ( ::sf::Matrix3::* )(  ) const)( &::sf::Matrix3::GetInverse ) )
        .def(
            "SetFromProjection"
            , (void ( ::sf::Matrix3::* )( ::sf::Vector2f const &,::sf::Vector2f const &,float ) )( &::sf::Matrix3::SetFromProjection )
            , ( bp::arg("center"), bp::arg("size"), bp::arg("rotation") ) )
        .def(
            "SetFromTransformations"
            , (void ( ::sf::Matrix3::* )( ::sf::Vector2f const &,::sf::Vector2f const &,float,::sf::Vector2f const & ) )( &::sf::Matrix3::SetFromTransformations )
            , ( bp::arg("origin"), bp::arg("translation"), bp::arg("rotation"), bp::arg("scale") ) )
        .def(
            "Transform"
            , (::sf::Vector2f ( ::sf::Matrix3::* )( ::sf::Vector2f const & ) const)( &::sf::Matrix3::Transform )
            , ( bp::arg("point") ) )
        .def(
            "__call__"
            , (float ( ::sf::Matrix3::* )( unsigned int,unsigned int ) const)( &::sf::Matrix3::operator() )
            , ( bp::arg("row"), bp::arg("column") ) )
        /*.def(
            "__call__"
            , (float & ( ::sf::Matrix3::* )( unsigned int,unsigned int ) )( &::sf::Matrix3::operator() )
            , ( bp::arg("row"), bp::arg("column") )
                /* undefined call policies  )*/
        .def( bp::self * bp::self )
        .def( bp::self *= bp::self )
        .def_readonly( "Identity", sf::Matrix3::Identity );

    bp::class_< sf::Vector3< float > >( "Vector3f", bp::init< >() )
        .def( bp::init< float, float, float >(( bp::arg("X"), bp::arg("Y"), bp::arg("Z") )) )
        .def_readwrite( "x", &sf::Vector3< float >::x )
        .def_readwrite( "y", &sf::Vector3< float >::y )
        .def_readwrite( "z", &sf::Vector3< float >::z );

    { //::sf::Sound
        typedef bp::class_< sf::Sound > Sound_exposer_t;
        Sound_exposer_t Sound_exposer = Sound_exposer_t( "Sound", bp::init< >() );
        bp::scope Sound_scope( Sound_exposer );
        bp::enum_< sf::Sound::Status>("Status")
            .value("Stopped", sf::Sound::Stopped)
            .value("Paused", sf::Sound::Paused)
            .value("Playing", sf::Sound::Playing)
            .export_values()
            ;
        Sound_exposer.def( bp::init< sf::SoundBuffer const &, bp::optional< bool, float, float, sf::Vector3f const & > >(( bp::arg("buffer"), bp::arg("loop")=(bool)(false), bp::arg("pitch")=1.0e+0f, bp::arg("volume")=1.0e+2f, bp::arg("position")=sf::Vector3<float>(0.0f, 0.0f, 0.0f) )) );
        Sound_exposer.def( bp::init< sf::Sound const & >(( bp::arg("copy") )) );
        { //::sf::Sound::GetAttenuation

            typedef float ( ::sf::Sound::*GetAttenuation_function_type )(  ) const;

            Sound_exposer.def(
                "GetAttenuation"
                , GetAttenuation_function_type( &::sf::Sound::GetAttenuation ) );

        }
        { //::sf::Sound::GetBuffer

            typedef ::sf::SoundBuffer const * ( ::sf::Sound::*GetBuffer_function_type )(  ) const;

            Sound_exposer.def(
                "GetBuffer"
                , GetBuffer_function_type( &::sf::Sound::GetBuffer )
                , bp::return_internal_reference< >() );

        }
        { //::sf::Sound::GetLoop

            typedef bool ( ::sf::Sound::*GetLoop_function_type )(  ) const;

            Sound_exposer.def(
                "GetLoop"
                , GetLoop_function_type( &::sf::Sound::GetLoop ) );

        }
        { //::sf::Sound::GetMinDistance

            typedef float ( ::sf::Sound::*GetMinDistance_function_type )(  ) const;

            Sound_exposer.def(
                "GetMinDistance"
                , GetMinDistance_function_type( &::sf::Sound::GetMinDistance ) );

        }
        { //::sf::Sound::GetPitch

            typedef float ( ::sf::Sound::*GetPitch_function_type )(  ) const;

            Sound_exposer.def(
                "GetPitch"
                , GetPitch_function_type( &::sf::Sound::GetPitch ) );

        }
        { //::sf::Sound::GetPlayingOffset

            typedef float ( ::sf::Sound::*GetPlayingOffset_function_type )(  ) const;

            Sound_exposer.def(
                "GetPlayingOffset"
                , GetPlayingOffset_function_type( &::sf::Sound::GetPlayingOffset ) );

        }
        { //::sf::Sound::GetPosition

            typedef ::sf::Vector3f ( ::sf::Sound::*GetPosition_function_type )(  ) const;

            Sound_exposer.def(
                "GetPosition"
                , GetPosition_function_type( &::sf::Sound::GetPosition ) );

        }
        { //::sf::Sound::GetStatus

            typedef ::sf::Sound::Status ( ::sf::Sound::*GetStatus_function_type )(  ) const;

            Sound_exposer.def(
                "GetStatus"
                , GetStatus_function_type( &::sf::Sound::GetStatus ) );

        }
        { //::sf::Sound::GetVolume

            typedef float ( ::sf::Sound::*GetVolume_function_type )(  ) const;

            Sound_exposer.def(
                "GetVolume"
                , GetVolume_function_type( &::sf::Sound::GetVolume ) );

        }
        { //::sf::Sound::IsRelativeToListener

            typedef bool ( ::sf::Sound::*IsRelativeToListener_function_type )(  ) const;

            Sound_exposer.def(
                "IsRelativeToListener"
                , IsRelativeToListener_function_type( &::sf::Sound::IsRelativeToListener ) );

        }
        { //::sf::Sound::Pause

            typedef void ( ::sf::Sound::*Pause_function_type )(  ) ;

            Sound_exposer.def(
                "Pause"
                , Pause_function_type( &::sf::Sound::Pause ) );

        }
        { //::sf::Sound::Play

            typedef void ( ::sf::Sound::*Play_function_type )(  ) ;

            Sound_exposer.def(
                "Play"
                , Play_function_type( &::sf::Sound::Play ) );

        }
        { //::sf::Sound::SetAttenuation

            typedef void ( ::sf::Sound::*SetAttenuation_function_type )( float ) ;

            Sound_exposer.def(
                "SetAttenuation"
                , SetAttenuation_function_type( &::sf::Sound::SetAttenuation )
                , ( bp::arg("attenuation") ) );

        }
        { //::sf::Sound::SetBuffer

            typedef void ( ::sf::Sound::*SetBuffer_function_type )( ::sf::SoundBuffer const & ) ;

            Sound_exposer.def(
                "SetBuffer"
                , SetBuffer_function_type( &::sf::Sound::SetBuffer )
                , ( bp::arg("buffer") ) );

        }
        { //::sf::Sound::SetLoop

            typedef void ( ::sf::Sound::*SetLoop_function_type )( bool ) ;

            Sound_exposer.def(
                "SetLoop"
                , SetLoop_function_type( &::sf::Sound::SetLoop )
                , ( bp::arg("loop") ) );

        }
        { //::sf::Sound::SetMinDistance

            typedef void ( ::sf::Sound::*SetMinDistance_function_type )( float ) ;

            Sound_exposer.def(
                "SetMinDistance"
                , SetMinDistance_function_type( &::sf::Sound::SetMinDistance )
                , ( bp::arg("distance") ) );

        }
        { //::sf::Sound::SetPitch

            typedef void ( ::sf::Sound::*SetPitch_function_type )( float ) ;

            Sound_exposer.def(
                "SetPitch"
                , SetPitch_function_type( &::sf::Sound::SetPitch )
                , ( bp::arg("pitch") ) );

        }
        { //::sf::Sound::SetPlayingOffset

            typedef void ( ::sf::Sound::*SetPlayingOffset_function_type )( float ) ;

            Sound_exposer.def(
                "SetPlayingOffset"
                , SetPlayingOffset_function_type( &::sf::Sound::SetPlayingOffset )
                , ( bp::arg("timeOffset") ) );

        }
        { //::sf::Sound::SetPosition

            typedef void ( ::sf::Sound::*SetPosition_function_type )( float,float,float ) ;

            Sound_exposer.def(
                "SetPosition"
                , SetPosition_function_type( &::sf::Sound::SetPosition )
                , ( bp::arg("x"), bp::arg("y"), bp::arg("z") ) );

        }
        { //::sf::Sound::SetPosition

            typedef void ( ::sf::Sound::*SetPosition_function_type )( ::sf::Vector3f const & ) ;

            Sound_exposer.def(
                "SetPosition"
                , SetPosition_function_type( &::sf::Sound::SetPosition )
                , ( bp::arg("position") ) );

        }
        { //::sf::Sound::SetRelativeToListener

            typedef void ( ::sf::Sound::*SetRelativeToListener_function_type )( bool ) ;

            Sound_exposer.def(
                "SetRelativeToListener"
                , SetRelativeToListener_function_type( &::sf::Sound::SetRelativeToListener )
                , ( bp::arg("relative") ) );

        }
        { //::sf::Sound::SetVolume

            typedef void ( ::sf::Sound::*SetVolume_function_type )( float ) ;

            Sound_exposer.def(
                "SetVolume"
                , SetVolume_function_type( &::sf::Sound::SetVolume )
                , ( bp::arg("volume") ) );

        }
        { //::sf::Sound::Stop

            typedef void ( ::sf::Sound::*Stop_function_type )(  ) ;

            Sound_exposer.def(
                "Stop"
                , Stop_function_type( &::sf::Sound::Stop ) );

        }
        { //::sf::Sound::operator=

            typedef ::sf::Sound & ( ::sf::Sound::*assign_function_type )( ::sf::Sound const & ) ;

            Sound_exposer.def(
                "assign"
                , assign_function_type( &::sf::Sound::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );

        }
    }

    { //::sf::SoundStream
        typedef bp::class_< sf::SoundStream, boost::noncopyable > SoundStream_exposer_t;
        SoundStream_exposer_t SoundStream_exposer = SoundStream_exposer_t( "SoundStream", bp::no_init );
        bp::scope SoundStream_scope( SoundStream_exposer );
        bp::class_< sf::SoundStream::Chunk >( "Chunk" )
            .def_readwrite( "NbSamples", &sf::SoundStream::Chunk::NbSamples );
        { //::sf::SoundStream::GetChannelsCount

            typedef unsigned int ( ::sf::SoundStream::*GetChannelsCount_function_type )(  ) const;

            SoundStream_exposer.def(
                "GetChannelsCount"
                , GetChannelsCount_function_type( &::sf::SoundStream::GetChannelsCount ) );

        }
        { //::sf::SoundStream::GetLoop

            typedef bool ( ::sf::SoundStream::*GetLoop_function_type )(  ) const;

            SoundStream_exposer.def(
                "GetLoop"
                , GetLoop_function_type( &::sf::SoundStream::GetLoop ) );

        }
        { //::sf::SoundStream::GetPlayingOffset

            typedef float ( ::sf::SoundStream::*GetPlayingOffset_function_type )(  ) const;

            SoundStream_exposer.def(
                "GetPlayingOffset"
                , GetPlayingOffset_function_type( &::sf::SoundStream::GetPlayingOffset ) );

        }
        { //::sf::SoundStream::GetSampleRate

            typedef unsigned int ( ::sf::SoundStream::*GetSampleRate_function_type )(  ) const;

            SoundStream_exposer.def(
                "GetSampleRate"
                , GetSampleRate_function_type( &::sf::SoundStream::GetSampleRate ) );

        }
        { //::sf::SoundStream::GetStatus

            typedef ::sf::Sound::Status ( ::sf::SoundStream::*GetStatus_function_type )(  ) const;

            SoundStream_exposer.def(
                "GetStatus"
                , GetStatus_function_type( &::sf::SoundStream::GetStatus ) );

        }
        { //::sf::SoundStream::Play

            typedef void ( ::sf::SoundStream::*Play_function_type )(  ) ;

            SoundStream_exposer.def(
                "Play"
                , Play_function_type( &::sf::SoundStream::Play ) );

        }
        { //::sf::SoundStream::SetLoop

            typedef void ( ::sf::SoundStream::*SetLoop_function_type )( bool ) ;

            SoundStream_exposer.def(
                "SetLoop"
                , SetLoop_function_type( &::sf::SoundStream::SetLoop )
                , ( bp::arg("loop") ) );

        }
        { //::sf::SoundStream::SetPlayingOffset

            typedef void ( ::sf::SoundStream::*SetPlayingOffset_function_type )( float ) ;

            SoundStream_exposer.def(
                "SetPlayingOffset"
                , SetPlayingOffset_function_type( &::sf::SoundStream::SetPlayingOffset )
                , ( bp::arg("timeOffset") ) );

        }
        { //::sf::SoundStream::Stop

            typedef void ( ::sf::SoundStream::*Stop_function_type )(  ) ;

            SoundStream_exposer.def(
                "Stop"
                , Stop_function_type( &::sf::SoundStream::Stop ) );

        }
    }
/*
    { //::sf::Music
        typedef bp::class_< sf::Music, bp::bases< sf::SoundStream >, boost::noncopyable > Music_exposer_t;
        Music_exposer_t Music_exposer = Music_exposer_t( "Music", bp::init< bp::optional< size_t > >(( bp::arg("bufferSize")=(unsigned int)(44100) )) );
        bp::scope Music_scope( Music_exposer );
        bp::implicitly_convertible< size_t, sf::Music >();
        { //::sf::Music::GetDuration

            typedef float ( ::sf::Music::*GetDuration_function_type )(  ) const;

            Music_exposer.def(
                "GetDuration"
                , GetDuration_function_type( &::sf::Music::GetDuration ) );

        }
        { //::sf::Music::OpenFromFile

            typedef bool ( ::sf::Music::*OpenFromFile_function_type )( ::std::string const & ) ;

            Music_exposer.def(
                "OpenFromFile"
                , OpenFromFile_function_type( &::sf::Music::OpenFromFile )
                , ( bp::arg("filename") ) );

        }
        { //::sf::Music::OpenFromMemory

            typedef bool ( ::sf::Music::*OpenFromMemory_function_type )( char const *,::size_t ) ;

            Music_exposer.def(
                "OpenFromMemory"
                , OpenFromMemory_function_type( &::sf::Music::OpenFromMemory )
                , ( bp::arg("data"), bp::arg("sizeInBytes") ) );

        }
    }*/

}
#endif
