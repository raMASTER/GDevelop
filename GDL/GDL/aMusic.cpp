#include <vector>
#include <string>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/aMusic.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/algo.h"
#include "GDL/Force.h"
#include <iostream>
#include "GDL/Access.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "GDL/RuntimeScene.h"
#include "GDL/constantes.h"
#include "GDL/RessourcesLoader.h"

struct est_fini
{
    bool operator ()( sf::Sound &a ) const
    {
        if (a.GetStatus() == sf::Sound::Stopped )
        {
            return true;
        }

        return false;
    }
};

////////////////////////////////////////////////////////////
/// Joue simplement un son
///
/// Type : PlaySound
/// Param�tre 1 : Fichier son
/// Param�tre 2 : Bouclage ( facultatif )
/// Param�tre 3 : Volume ( facultatif )
////////////////////////////////////////////////////////////
bool ActPlaySound( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    sf::Clock Latence;

    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    Son * son = new Son(action.GetParameter(0).GetPlainString());
    soundManager->sounds.push_back(son);
    soundManager->sounds.back()->sound.Play();

    //Compatibilit� avec Game Develop 1.0.1979 et inf�rieur
    //On verifie si l'argument 2 ( Bouclage ) existe
    if ( action.GetParameters().size() > 1 )
    {
        if ( action.GetParameter(1).GetPlainString() == "oui" || action.GetParameter(1).GetPlainString() == "yes" )
        {
            soundManager->sounds.back()->sound.SetLoop(true);
        }
    }

    //Compatibilit� avec Game Develop 1.1.5429 et inf�rieur
    //On verifie si l'argument 3 ( Volume ) existe
    if ( action.GetParameters().size() > 2 )
    {
        if ( action.GetParameter(2).GetPlainString() != "" )
            soundManager->sounds.back()->SetVolume(eval.EvalExp(action.GetParameter(2)));
        else
            soundManager->sounds.back()->SetVolume(100);
    }


    scene->pauseTime += Latence.GetElapsedTime();

    return true;
}

////////////////////////////////////////////////////////////
/// Joue un son sur un canal
///
/// Type : PlaySoundCanal
/// Param�tre 1 : Fichier son
/// Param�tre 2 : Canal
/// Param�tre 3 : Bouclage ( fac )
/// Param�tre 4 : Volume ( fac )
////////////////////////////////////////////////////////////
bool ActPlaySoundCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(1)) );

    if ( canal < 0 || canal > MAX_CANAUX_SON )
    {
        scene->errors.Add("Canal invalide pour jouer le son", "", "", -1, 1);
        return false;
    }

    //Chargement
    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    //Son � jouer
    Son * son = new Son(action.GetParameter(0).GetPlainString());
    son->sound.Play();

    soundManager->SetSoundOnChannel(canal, son);

    //Compatibilit� avec Game Develop 1.0.1979 et inf�rieur
    //On verifie si l'argument 3 ( Bouclage ) existe
    if ( action.GetParameters().size() > 2 )
    {
        if ( action.GetParameter(2).GetPlainString() == "oui" || action.GetParameter(2).GetPlainString() == "yes" )
        {
            soundManager->GetSoundOnChannel(canal)->sound.SetLoop(true);
        }
    }

    //Compatibilit� avec Game Develop 1.1.5429 et inf�rieur
    //On verifie si l'argument 4 ( Volume ) existe
    if ( action.GetParameters().size() > 3 )
    {
        if ( action.GetParameter(3).GetPlainString() != "" )
            soundManager->GetSoundOnChannel(canal)->SetVolume(eval.EvalExp(action.GetParameter(3)));
        else
            soundManager->GetSoundOnChannel(canal)->SetVolume(100);
    }

    return true;
}


////////////////////////////////////////////////////////////
/// Stoppe un son sur un canal
///
/// Type : StopSoundCanal
/// Param�tre 1 : Canal
////////////////////////////////////////////////////////////
bool ActStopSoundCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_SON )
    {
        scene->errors.Add("Canal invalide pour jouer le son", "", "", -1, 1);
        return false;
    }

    //Chargement
    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    soundManager->GetSoundOnChannel(canal)->sound.Stop();

    return true;
}

////////////////////////////////////////////////////////////
/// Met en pause un son sur un canal
///
/// Type : PauseSoundCanal
/// Param�tre 1 : Canal
////////////////////////////////////////////////////////////
bool ActPauseSoundCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_SON )
    {
        scene->errors.Add("Canal invalide pour jouer le son", "", "", -1, 1);
        return false;
    }

    //Chargement
    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    soundManager->GetSoundOnChannel(canal)->sound.Pause();

    return true;
}

////////////////////////////////////////////////////////////
/// Re(joute) un son sur un canal
///
/// Type : RePlaySoundCanal
/// Param�tre 1 : Canal
////////////////////////////////////////////////////////////
bool ActRePlaySoundCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_SON )
    {
        scene->errors.Add("Canal invalide pour jouer le son", "", "", -1, 1);
        return false;
    }

    //Chargement
    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    soundManager->GetSoundOnChannel(canal)->sound.Play();

    return true;
}

////////////////////////////////////////////////////////////
/// Joue simplement une musique
///
/// Type : PlayMusic
/// Param�tre 1 : Fichier
/// Param�tre 2 : Bouclage ( facultatif )
/// Param�tre 3 : Volume ( facultatif )
////////////////////////////////////////////////////////////
bool ActPlayMusic( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    SoundManager * soundManager = SoundManager::getInstance();
    RessourcesLoader * ressourcesLoader = RessourcesLoader::getInstance();

    Music * music = ressourcesLoader->LoadMusic(action.GetParameter(0).GetPlainString()); //Chargement

    soundManager->musics.push_back(music); //Ajout aux soundManager qui prend en charge la musique
    soundManager->musics.at(soundManager->musics.size()-1)->Play();

    //Compatibilit� avec Game Develop 1.0.1979 et inf�rieur
    //On verifie si l'argument 2 ( Bouclage ) existe
    if ( action.GetParameters().size() > 1 )
    {
        if ( action.GetParameter(1).GetPlainString() == "oui" || action.GetParameter(1).GetPlainString() == "yes" )
        {
            music->SetLoop(true);
        }
    }

    //Compatibilit� avec Game Develop 1.1.5429 et inf�rieur
    //On verifie si l'argument 3 ( Volume ) existe
    if ( action.GetParameters().size() > 2 )
    {
        if ( action.GetParameter(2).GetPlainString() != "" )
            music->SetVolume(eval.EvalExp(action.GetParameter(2)));
        else
            music->SetVolume(100);
    }


    return true;
}


////////////////////////////////////////////////////////////
/// Joue une musique sur un canal
///
/// Type : PlayMusicCanal
/// Param�tre 1 : Fichier
/// Param�tre 2 : Canal
/// Param�tre 3 : Bouclage ( facultatif )
////////////////////////////////////////////////////////////
bool ActPlayMusicCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(1)));

    if ( canal < 0 || canal > MAX_CANAUX_MUSIC )
    {
        scene->errors.Add("Canal invalide pour jouer la musique", "", "", -1, 1);
        return false;
    }

    SoundManager * soundManager = SoundManager::getInstance();
    RessourcesLoader * ressourcesLoader = RessourcesLoader::getInstance();

    Music * music = ressourcesLoader->LoadMusic(action.GetParameter(0).GetPlainString()); //Chargement
    music->Play();

    soundManager->SetMusicOnChannel(canal, music); //Ajout au soundManager qui prend en charge la music

    //Compatibilit� avec Game Develop 1.0.1979 et inf�rieur
    //On verifie si l'argument 3 ( Bouclage ) existe
    if ( action.GetParameters().size() > 2 )
    {
        if ( action.GetParameter(2).GetPlainString() == "oui" || action.GetParameter(2).GetPlainString() == "yes" )
        {
            music->SetLoop(true);
        }
    }

    //Compatibilit� avec Game Develop 1.1.5429 et inf�rieur
    //On verifie si l'argument 4 ( Volume ) existe
    if ( action.GetParameters().size() > 3 )
    {
        if ( action.GetParameter(3).GetPlainString() != "" )
            music->SetVolume(eval.EvalExp(action.GetParameter(3)));
        else
            music->SetVolume(100);
    }
    return true;
}

////////////////////////////////////////////////////////////
/// Stoppe une musique sur un canal
///
/// Type : StopMusicCanal
/// Param�tre 1 : Canal
////////////////////////////////////////////////////////////
bool ActStopMusicCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_MUSIC )
    {
        scene->errors.Add("Canal invalide pour jouer la musique", "", "", -1, 1);
        return false;
    }

    //Chargement
    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    soundManager->GetMusicOnChannel(canal)->Stop();

    return true;
}

////////////////////////////////////////////////////////////
/// Met en pause une musique sur un canal
///
/// Type : PauseMusicCanal
/// Param�tre 1 : Canal
////////////////////////////////////////////////////////////
bool ActPauseMusicCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_MUSIC )
    {
        scene->errors.Add("Canal invalide pour jouer la musique", "", "", -1, 1);
        return false;
    }

    //Chargement
    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    soundManager->GetMusicOnChannel(canal)->Pause();

    return true;
}

////////////////////////////////////////////////////////////
/// Re(joute) une musique sur un canal
///
/// Type : RePlayMusicCanal
/// Param�tre 1 : Canal
////////////////////////////////////////////////////////////
bool ActRePlayMusicCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> ( eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_MUSIC )
    {
        scene->errors.Add("Canal invalide pour jouer la musique", "", "", -1, 1);
        return false;
    }

    //Chargement
    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    soundManager->GetMusicOnChannel(canal)->Play();

    return true;
}

////////////////////////////////////////////////////////////
/// Modifier le volume du son sur le canal
///
/// Type : ModVolumeSoundCanal
/// Param�tre 1 : Canal
/// Param�tre 2 : Volume
/// Param�tre 3 : Signe ( facultatif )
////////////////////////////////////////////////////////////
bool ActModVolumeSoundCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> (eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_SON )
    {
        scene->errors.Add("Canal invalide pour jouer la musique", "", "", -1, 1);
        return false;
    }

    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    if (action.GetParameter(2).GetPlainString().empty() || action.GetParameter(2).GetAsModOperator() == GDExpression::Set)
        soundManager->GetSoundOnChannel(canal)->SetVolume(eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Add)
        soundManager->GetSoundOnChannel(canal)->SetVolume(soundManager->GetSoundOnChannel(canal)->GetVolume() + eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Substract)
        soundManager->GetSoundOnChannel(canal)->SetVolume(soundManager->GetSoundOnChannel(canal)->GetVolume() - eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Multiply)
        soundManager->GetSoundOnChannel(canal)->SetVolume(soundManager->GetSoundOnChannel(canal)->GetVolume() * eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Divide)
        soundManager->GetSoundOnChannel(canal)->SetVolume(soundManager->GetSoundOnChannel(canal)->GetVolume() / eval.EvalExp(action.GetParameter(1)));

    return true;
}


////////////////////////////////////////////////////////////
/// Modifier le volume d'une musique sur le canal
///
/// Type : ModVolumeMusicCanal
/// Param�tre 1 : Canal
/// Param�tre 2 : Volume
/// Param�tre 3 : Signe ( facultatif )
////////////////////////////////////////////////////////////
bool ActModVolumeMusicCanal( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    int canal = static_cast<int> (eval.EvalExp(action.GetParameter(0)));

    if ( canal < 0 || canal > MAX_CANAUX_MUSIC )
    {
        scene->errors.Add("Canal invalide pour jouer la musique", "", "", -1, 1);
        return false;
    }

    SoundManager * soundManager;
    soundManager = SoundManager::getInstance();

    if (action.GetParameter(2).GetPlainString().empty() || action.GetParameter(2).GetAsModOperator() == GDExpression::Set)
        soundManager->GetMusicOnChannel(canal)->SetVolume(eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Add)
        soundManager->GetMusicOnChannel(canal)->SetVolume(soundManager->GetMusicOnChannel(canal)->GetVolume() + eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Substract)
        soundManager->GetMusicOnChannel(canal)->SetVolume(soundManager->GetMusicOnChannel(canal)->GetVolume() - eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Multiply)
        soundManager->GetMusicOnChannel(canal)->SetVolume(soundManager->GetMusicOnChannel(canal)->GetVolume() * eval.EvalExp(action.GetParameter(1)));
    else if (action.GetParameter(2).GetAsModOperator() == GDExpression::Divide)
        soundManager->GetMusicOnChannel(canal)->SetVolume(soundManager->GetMusicOnChannel(canal)->GetVolume() / eval.EvalExp(action.GetParameter(1)));

    return true;
}

////////////////////////////////////////////////////////////
/// Modifier le volume global du jeu
///
/// Type : ModGlobalVolume
/// Param�tre 2 : Volume
/// Param�tre 3 : Signe ( facultatif )
////////////////////////////////////////////////////////////
bool ActModGlobalVolume( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    SoundManager * soundManager = SoundManager::getInstance();

    if (action.GetParameter(1).GetPlainString().empty() || action.GetParameter(1).GetAsModOperator() == GDExpression::Set)
        soundManager->SetGlobalVolume(eval.EvalExp(action.GetParameter(0)));
    else if (action.GetParameter(1).GetAsModOperator() == GDExpression::Add)
        soundManager->SetGlobalVolume(soundManager->GetGlobalVolume() + eval.EvalExp(action.GetParameter(0)));
    else if (action.GetParameter(1).GetAsModOperator() == GDExpression::Substract)
        soundManager->SetGlobalVolume(soundManager->GetGlobalVolume() - eval.EvalExp(action.GetParameter(0)));
    else if (action.GetParameter(1).GetAsModOperator() == GDExpression::Multiply)
        soundManager->SetGlobalVolume(soundManager->GetGlobalVolume() * eval.EvalExp(action.GetParameter(0)));
    else if (action.GetParameter(1).GetAsModOperator() == GDExpression::Divide)
        soundManager->SetGlobalVolume(soundManager->GetGlobalVolume() / eval.EvalExp(action.GetParameter(0)));

    return true;
}
