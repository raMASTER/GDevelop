#include "GDL/cObjet.h"

#include <vector>
#include <string>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/cADS.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/algo.h"
#include "GDL/Force.h"
#include <iostream>
#include "GDL/Access.h"
#include "GDL/RuntimeScene.h"
#include "GDL/ObjectsConcerned.h"

#include "GDL/Instruction.h"

////////////////////////////////////////////////////////////
/// Test du nombre d'objet
///
/// Type : NbObjet
/// Param�tre 1 : Nom de l'objet
/// Param�tre 2 : Nombre � tester
/// Param�tre 3 : Signe du test
////////////////////////////////////////////////////////////
bool CondNbObjet( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & condition, const Evaluateur & eval )
{
    ObjectsConcerned originalObjectsConcerned = objectsConcerned;
    eval.SetObjectsConcerned(&originalObjectsConcerned);

    ObjList list = objectsConcerned.PickAndRemove(condition.GetParameter( 0 ).GetPlainString(), condition.IsGlobal());
    bool isTrue = false;

    //optimisation : le test de signe en premier
    if (( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Equal && list.size() == eval.EvalExp( condition.GetParameter( 1 ) ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Inferior && list.size() < eval.EvalExp( condition.GetParameter( 1 ) ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Superior && list.size() > eval.EvalExp( condition.GetParameter( 1 ) ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && list.size() <= eval.EvalExp( condition.GetParameter( 1 ) ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && list.size() >= eval.EvalExp( condition.GetParameter( 1 ) ) ) ||
            ( condition.GetParameter( 2 ).GetAsCompOperator() == GDExpression::Different && list.size() != eval.EvalExp( condition.GetParameter( 1 ) ) )
       )
    {
        //Le nombre d'objet est ok
        if ( !condition.IsInverted() ) isTrue = true;
    }
    else
    {
        if ( condition.IsInverted() ) isTrue = true;
    }

    //Pour chaque objet concern�
    //TODO : ?
	ObjList::iterator obj = list.begin();
	ObjList::const_iterator obj_end = list.end();
    for ( ; obj != obj_end; ++obj )
    {
        objectsConcerned.objectsPicked.push_back(*obj);
    }

    return isTrue;
}

////////////////////////////////////////////////////////////
/// Ajouter des objets aux objet concern�s
///
/// Type : AjoutObjConcern
/// Param�tre 1 : Objet � ajouter
////////////////////////////////////////////////////////////
bool CondAjoutObjConcern( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & condition, const Evaluateur & eval )
{
    ObjList list = objectsConcerned.PickAndRemove(condition.GetParameter( 0 ).GetPlainString(), condition.IsGlobal());

	ObjList::iterator obj = list.begin();
	ObjList::const_iterator obj_end = list.end();
    for ( ; obj != obj_end; ++obj )
    {
        objectsConcerned.objectsPicked.push_back(*obj);
    }

    return true;
}

////////////////////////////////////////////////////////////
/// Ajouter un objet au hasard ayant le nom indiqu� aux objet concern�s
///
/// Type : AjoutHasard
/// Param�tre 1 : Objet � ajouter
////////////////////////////////////////////////////////////
bool CondAjoutHasard( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & condition, const Evaluateur & eval )
{
    ObjList list = objectsConcerned.PickAndRemove(condition.GetParameter( 0 ).GetPlainString(), condition.IsGlobal());

    //On en reprend un dans la liste
    if ( !list.empty() )
    {
        int id = sf::Randomizer::Random(0, list.size()-1);
        objectsConcerned.objectsPicked.push_back(list[id]);
    }


    return true;
}
