/////////////////////////////////////////////////////////////////////////////
// Name:        beamspan.cpp
// Author:      Stefan Münnich
// Created:     30/05/2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "beamspan.h"

//----------------------------------------------------------------------------

#include <assert.h>
#include <math.h>

//----------------------------------------------------------------------------

#include "chord.h"
#include "doc.h"
#include "editorial.h"
#include "elementpart.h"
#include "functorparams.h"
#include "layer.h"
#include "layerelement.h"
#include "note.h"
#include "rest.h"
#include "smufl.h"
#include "space.h"
#include "staff.h"
#include "tuplet.h"
#include "verticalaligner.h"
#include "vrv.h"

namespace vrv {
    
    //----------------------------------------------------------------------------
    // BeamSpan
    //----------------------------------------------------------------------------
    
    BeamSpan::BeamSpan() : ControlElement("beamspan-"), ObjectListInterface(),TimeSpanningInterface(), AttColor(), AttPlacement()
    {
        RegisterInterface(TimeSpanningInterface::GetAttClasses(), TimeSpanningInterface::IsInterface());
        RegisterAttClass(ATT_COLOR);
        RegisterAttClass(ATT_PLACEMENT);
        
        Reset();
    }
    
    BeamSpan::~BeamSpan()
    {
        ClearCoords();
    }
    
    void BeamSpan::Reset(){
        ControlElement::Reset();
        TimeSpanningInterface::Reset();
        ResetColor();
        ResetPlacement();
        
        ClearCoords();
    }
    
    void BeamSpan::ClearCoords()
    {
        ArrayOfBeamElementCoords::iterator iter;
        for (iter = m_beamElementCoords.begin(); iter != m_beamElementCoords.end(); ++iter) {
            delete *iter;
        }
        m_beamElementCoords.clear();
    }
    
    //----------------------------------------------------------------------------
    // BeamSpanElementCoord
    //----------------------------------------------------------------------------
    
    /**
     BeamSpanElementCoord::~BeamSpanElementCoord()
     {
     if (m_element) m_element->m_beamElementCoord = NULL;
     }
     **/
    
    
    
} // namespace vrv
