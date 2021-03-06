/////////////////////////////////////////////////////////////////////////////
// Name:        turn.cpp
// Author:      Klaus Rettinghaus
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "turn.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "smufl.h"
#include "verticalaligner.h"

namespace vrv {

//----------------------------------------------------------------------------
// Turn
//----------------------------------------------------------------------------

static const ClassRegistrar<Turn> s_factory("turn", TURN);

Turn::Turn()
    : ControlElement("turn-")
    , TimePointInterface()
    , AttColor()
    , AttExtSym()
    , AttOrnamentAccid()
    , AttPlacementRelStaff()
    , AttTurnLog()
{
    RegisterInterface(TimePointInterface::GetAttClasses(), TimePointInterface::IsInterface());
    RegisterAttClass(ATT_COLOR);
    RegisterAttClass(ATT_EXTSYM);
    RegisterAttClass(ATT_ORNAMENTACCID);
    RegisterAttClass(ATT_PLACEMENTRELSTAFF);
    RegisterAttClass(ATT_TURNLOG);

    Reset();
}

Turn::~Turn() {}

void Turn::Reset()
{
    ControlElement::Reset();
    TimePointInterface::Reset();
    ResetColor();
    ResetExtSym();
    ResetOrnamentAccid();
    ResetPlacementRelStaff();
    ResetTurnLog();
}

wchar_t Turn::GetTurnGlyph() const
{
    // If there is glyph.num, prioritize it
    if (HasGlyphNum()) {
        wchar_t code = GetGlyphNum();
        if (NULL != Resources::GetGlyph(code)) return code;
    }
    // If there is glyph.name (second priority)
    else if (HasGlyphName()) {
        wchar_t code = Resources::GetGlyphCode(GetGlyphName());
        if (NULL != Resources::GetGlyph(code)) return code;
    }

    return (GetForm() == turnLog_FORM_lower) ? SMUFL_E568_ornamentTurnInverted : SMUFL_E567_ornamentTurn;
}

//----------------------------------------------------------------------------
// Turn functor methods
//----------------------------------------------------------------------------

} // namespace vrv
