/////////////////////////////////////////////////////////////////////////////
// Name:        beamspan.h
// Author:      Stefan Münnich
// Created:     30/05/2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_BEAMSPAN_H__
#define __VRV_BEAMSPAN_H__

#include "atts_cmn.h"
#include "controlelement.h"
#include "drawinginterface.h"
#include "timeinterface.h"

namespace vrv {

// the maximum allowed number of partials
#define MAX_DURATION_PARTIALS 16
    
// enum { PARTIAL_NONE = 0, PARTIAL_THROUGH, PARTIAL_RIGHT, PARTIAL_LEFT };

//----------------------------------------------------------------------------
// BeamSpanDrawingParams
//----------------------------------------------------------------------------

/**
 * Class for storing drawing parameters when calculating beamspans.
 * See View::DrawBeamSpan and View::CalcBeamSpan
 * This could be turned into a BeamSpanDrawingInterface
 */

class BeamSpanDrawingParams {
public:
    /**
     * @name Constructors, destructors, and other standard methods
     */
    ///@{
    BeamSpanDrawingParams();
    virtual ~BeamSpanDrawingParams() {}
    
    void Reset();
    
    void CalcBeamSpan(Layer *layer, Staff *staff, Doc *doc, const ArrayOfBeamElementCoords *beamElementCoords, int elementCount);
    
    // values to be set before calling CalcBeamSpan
    bool m_changingDur;
    bool m_beamSpanHasChord;
    bool m_hasMultipleStemDir;
    bool m_cueSize;
    int m_shortestDur;
    data_STEMDIRECTION m_stemDir;
    
    // values set by CalcBeamSpan
    int m_beamSpanWidth;
    int m_beamSpanWidthBlack;
    int m_beamSpanWidthWhite;
    double m_startingY; // the initial position of the beamSpan
    double m_beamSpanSlope; // the slope of the beamSpan
    double m_verticalBoost; // extra height to ensure the beamSpan clears all the noteheads
};

//----------------------------------------------------------------------------
// BeamSpan
//----------------------------------------------------------------------------

class BeamSpan : public ControlElement,
                 public ObjectListInterface,
                 public DrawingListInterface,
                 public TimeSpanningInterface,
                 public AttColor,
                 public AttPlacement {
public:
    /**
     * @name Constructors, destructors, and other standard methods
     * Reset method resets all attribute classes.
     */
    ///@{
    BeamSpan();
    virtual ~BeamSpan();
    virtual void Reset();
    virtual std::string GetClassName() const { return "BeamSpan"; }
    virtual ClassId GetClassId() const { return BEAMSPAN; }
    ///@}
    
    /**
     * @name Getter to interfaces
     */
    ///@{
    virtual TimePointInterface *GetTimePointInterface() { return dynamic_cast<TimePointInterface *>(this); }
    virtual TimeSpanningInterface *GetTimeSpanningInterface() { return dynamic_cast<TimeSpanningInterface *>(this); }
    ///@}
    
    /** TODO: No child note
     * Return information about the position in the beam.
     * (no const since the cached list is updated)
     */
    ///@{
    bool IsFirstInBeamSpan(LayerElement *element);
    bool IsLastInBeamSpan(LayerElement *element);
    ///@}
    
    /**
     *
     */
    const ArrayOfBeamElementCoords *GetElementCoords() const { return &m_beamElementCoords; }
    
    //----------//
    // Functors //
    //----------//
    
    /**
     * See Object::CalcStem
     */
    // virtual int CalcStem(FunctorParams *functorParams);
    
protected:
    /**
     * Filter the list for a specific class.
     * For example, keep only notes in Beam
     * This also initializes the m_beamElementCoords vector
     */
    // virtual void FilterList(ListOfObjects *childList);

    /**
     * Initializes the m_beamElementCoords vector objects.
     * This is called by Beam::FilterList
     */
    void InitCoords(ListOfObjects *childList);
    
    /**
     * Return the position of the element in the beam.
     * For notes, lookup the position of the parent chord.
     */
    // int GetPosition(LayerElement *element);
    
    /**
     * Clear the m_beamElementCoords vector and delete all the objects.
     */
    void ClearCoords();
    
private:
    //
public:
    /** */
    // BeamSpanDrawingParams m_drawingParams;
    
private:
    /**
     * An array of coordinates for each element
     **/
     mutable ArrayOfBeamElementCoords m_beamElementCoords;
};

//----------------------------------------------------------------------------
// BeamSpanElementCoord
//----------------------------------------------------------------------------

class BeamSpanElementCoord {
public:
    /**
     * @name Constructors, destructors, and other standard methods
     */
    ///@{
    BeamSpanElementCoord() { m_element = NULL; }
    virtual ~BeamSpanElementCoord();
    
    int m_x;
    int m_y; // represents the point farthest from the beam
    int m_yTop; // y value of topmost note
    int m_yBottom; // y value of bottom-most note
    int m_yBeam; // y value of stem top position
    int m_dur; // drawing duration
    int m_breaksec;
    char m_partialFlags[MAX_DURATION_PARTIALS];
    ControlElement *m_element;
};
    
} // namespace vrv


#endif
