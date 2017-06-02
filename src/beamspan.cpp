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

#include "beam.h"
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
    // BeamSpanDrawingParams
    //----------------------------------------------------------------------------
    
    BeamSpanDrawingParams::BeamSpanDrawingParams()
    {
        Reset();
    }
    
    void BeamSpanDrawingParams::Reset()
    {
        m_changingDur = false;
        m_beamSpanHasChord = false;
        m_hasMultipleStemDir = false;
        m_cueSize = false;
        m_shortestDur = 0;
        m_stemDir = STEMDIRECTION_NONE;
    }
    
    void BeamSpanDrawingParams::CalcBeamSpan(
        Layer *layer, Staff *staff, Doc *doc, const ArrayOfBeamElementCoords *beamSpanElementCoords, int elementCount)
    {
        assert(layer);
        assert(staff);
        assert(doc);
        
        int y1, y2, avgY, high, low, verticalCenter, verticalShift;
        double xr, verticalShiftFactor;
        
        // loop
        int i;
        
        // position x for the stem (normal and cue-sized)
        int stemX[2];
        
        // For slope calculation and linear regression
        double s_x = 0.0; // sum of all x(n) for n in beamElementCoord
        double s_y = 0.0; // sum of all y(n)
        double s_xy = 0.0; // sum of (x(n) * y(n))
        double s_x2 = 0.0; // sum of all x(n)^2
        double s_y2 = 0.0; // sum of all y(n)^2
    
        /******************************************************************/
        // initialization
        
        for (i = 0; i < elementCount; i++) {
            (*beamSpanElementCoords).at(i)->m_x = (*beamSpanElementCoords).at(i)->m_element->GetDrawingX();
        }
        
        avgY = 0;
        high = VRV_UNSET;
        low = -VRV_UNSET;
        this->m_verticalBoost = 0.0;
        
        verticalShiftFactor = 3.0;
        verticalCenter = staff->GetDrawingY()
        - (doc->GetDrawingDoubleUnit(staff->m_drawingStaffSize) * 2); // center point of the staff
        
        int last = elementCount - 1;
        
        // x-offset values for stem bases, dx[y] where y = element->m_cueSize
        stemX[0] = doc->GetGlyphWidth(SMUFL_E0A3_noteheadHalf, staff->m_drawingStaffSize, false) / 2
        - (doc->GetDrawingStemWidth(staff->m_drawingStaffSize)) / 2;
        stemX[1] = doc->GetGlyphWidth(SMUFL_E0A3_noteheadHalf, staff->m_drawingStaffSize, true) / 2
        - (doc->GetDrawingStemWidth(staff->m_drawingStaffSize)) / 2;
        
        /******************************************************************/
        // Calculate the extreme values
        
        int yMax = 0, yMin = 0;
        int curY;
        // elementCount holds the last one
        for (i = 0; i < elementCount; i++) {
            
            if ((*beamSpanElementCoords).at(i)->m_element->Is(CHORD)) {
                Chord *chord = dynamic_cast<Chord *>((*beamSpanElementCoords).at(i)->m_element);
                assert(chord);
                chord->GetYExtremes(yMax, yMin);
                (*beamSpanElementCoords).at(i)->m_yTop = yMax;
                (*beamSpanElementCoords).at(i)->m_yBottom = yMin;
                
                avgY += ((yMax + yMin) / 2);
                
                // highest and lowest value;
                high = std::max(yMax, high);
                low = std::min(yMin, low);
            }
            else {
                (*beamSpanElementCoords).at(i)->m_y = (*beamSpanElementCoords).at(i)->m_element->GetDrawingY();
                
                // highest and lowest value;
                high = std::max((*beamSpanElementCoords).at(i)->m_y, high);
                low = std::min((*beamSpanElementCoords).at(i)->m_y, low);
                
                curY = (*beamSpanElementCoords).at(i)->m_element->GetDrawingY();
                (*beamSpanElementCoords).at(i)->m_yTop = curY;
                (*beamSpanElementCoords).at(i)->m_yBottom = curY;
                avgY += (*beamSpanElementCoords).at(i)->m_y;
            }
        }
        
        /******************************************************************/
        // Set the stem direction
        
        // yExtreme = (abs(high - verticalCenter) > abs(low - verticalCenter) ? high : low);
        avgY /= elementCount;
        
        // If we have one stem direction in the beam, then don't look at the layer
        if (this->m_stemDir == STEMDIRECTION_NONE)
            this->m_stemDir = layer->GetDrawingStemDir(); // force layer direction if it exists
        
        // Automatic stem direction if nothing in the notes or in the layer
        if (this->m_stemDir == STEMDIRECTION_NONE) {
            /*if (this->m_beamHasChord)
             this->m_stemDir = (yExtreme < verticalCenter)
             ? STEMDIRECTION_up
             : STEMDIRECTION_down; // if it has a chord, go by the most extreme position
             else */
            this->m_stemDir = (avgY < verticalCenter) ? STEMDIRECTION_up : STEMDIRECTION_down; // otherwise go by average
        }
        
        if (this->m_stemDir == STEMDIRECTION_up) { // set stem direction for all the notes
            for (i = 0; i < elementCount; i++) {
                (*beamSpanElementCoords).at(i)->m_y = (*beamSpanElementCoords).at(i)->m_yTop;
            }
        }
        else {
            for (i = 0; i < elementCount; i++) {
                (*beamSpanElementCoords).at(i)->m_y = (*beamSpanElementCoords).at(i)->m_yBottom;
            }
        }
        
        this->m_beamSpanWidthBlack = doc->GetDrawingBeamWidth(staff->m_drawingStaffSize, this->m_cueSize);
        this->m_beamSpanWidthWhite = doc->GetDrawingBeamWhiteWidth(staff->m_drawingStaffSize, this->m_cueSize);
        this->m_beamSpanWidth = this->m_beamSpanWidthBlack + this->m_beamSpanWidthWhite;
        
        /******************************************************************/
        // Calculate the slope doing a linear regression
        
        // The vertical shift depends on the shortestDur value we have in the beam
        verticalShift = ((this->m_shortestDur - DUR_8) * (this->m_beamSpanWidth));
        
        // if the beam has smaller-size notes
        if ((*beamSpanElementCoords).at(last)->m_element->IsCueSize()) {
            verticalShift += doc->GetDrawingUnit(staff->m_drawingStaffSize) * 5;
        }
        else {
            verticalShift += (this->m_shortestDur > DUR_8)
            ? doc->GetDrawingDoubleUnit(staff->m_drawingStaffSize) * verticalShiftFactor
            : doc->GetDrawingDoubleUnit(staff->m_drawingStaffSize) * (verticalShiftFactor + 0.5);
        }
        
        // swap x position and verticalShift direction with stem down
        if (this->m_stemDir == STEMDIRECTION_down) {
            stemX[0] = -stemX[0];
            stemX[1] = -stemX[1];
            verticalShift = -verticalShift;
        }
        
        for (i = 0; i < elementCount; i++) {
            // change the stem dir for all objects
            if ((*beamSpanElementCoords).at(i)->m_element->Is(NOTE)) {
                ((Note *)(*beamSpanElementCoords).at(i)->m_element)->SetDrawingStemDir(this->m_stemDir);
            }
            else if ((*beamSpanElementCoords).at(i)->m_element->Is(CHORD)) {
                ((Chord *)(*beamSpanElementCoords).at(i)->m_element)->SetDrawingStemDir(this->m_stemDir);
            }
            
            (*beamSpanElementCoords).at(i)->m_yBeam = (*beamSpanElementCoords).at(i)->m_y + verticalShift;
            (*beamSpanElementCoords).at(i)->m_x += stemX[this->m_cueSize];
            
            s_y += (*beamSpanElementCoords).at(i)->m_yBeam;
            s_y2 += (*beamSpanElementCoords).at(i)->m_yBeam * (*beamSpanElementCoords).at(i)->m_yBeam;
            s_x += (*beamSpanElementCoords).at(i)->m_x;
            s_x2 += (*beamSpanElementCoords).at(i)->m_x * (*beamSpanElementCoords).at(i)->m_x;
            s_xy += (*beamSpanElementCoords).at(i)->m_x * (*beamSpanElementCoords).at(i)->m_yBeam;
        }
        
        y1 = elementCount * s_xy - s_x * s_y;
        xr = elementCount * s_x2 - s_x * s_x;
        
        // Prevent division by 0
        if (y1 && xr) {
            this->m_beamSpanSlope = y1 / xr;
        }
        else {
            this->m_beamSpanSlope = 0.0;
        }
        
        /* Correction esthetique : */
        if (fabs(this->m_beamSpanSlope) < doc->m_drawingBeamMinSlope) this->m_beamSpanSlope = 0.0;
        if (fabs(this->m_beamSpanSlope) > doc->m_drawingBeamMaxSlope)
            this->m_beamSpanSlope = (this->m_beamSpanSlope > 0) ? doc->m_drawingBeamMaxSlope : -doc->m_drawingBeamMaxSlope;
        /* pente correcte: entre 0 et env 0.4 (0.2 a 0.4) */
        
        this->m_startingY = (s_y - this->m_beamSpanSlope * s_x) / elementCount;
        
        /******************************************************************/
        // Calculate the stem lengths
        
        // first check that the stem length is long enough (to be improved?)
        double oldYPos; // holds y position before calculation to determine if beam needs extra height
        double expectedY;
        for (i = 0; i < elementCount; i++) {
            oldYPos = (*beamSpanElementCoords).at(i)->m_yBeam;
            expectedY = this->m_startingY + this->m_verticalBoost + this->m_beamSpanSlope * (*beamSpanElementCoords).at(i)->m_x;
            
            // if the stem is not long enough, add extra stem length needed to all members of the beam
            if ((this->m_stemDir == STEMDIRECTION_up && (oldYPos > expectedY))
                || (this->m_stemDir == STEMDIRECTION_down && (oldYPos < expectedY))) {
                this->m_verticalBoost += oldYPos - expectedY;
            }
        }
        for (i = 0; i < elementCount; i++) {
            (*beamSpanElementCoords).at(i)->m_yBeam
            = this->m_startingY + this->m_verticalBoost + this->m_beamSpanSlope * (*beamSpanElementCoords).at(i)->m_x;
        }
        
        // then check that the stem length reaches the center for the staff
        double minDistToCenter = -VRV_UNSET;
        for (i = 0; i < elementCount; i++) {
            if ((this->m_stemDir == STEMDIRECTION_up)
                && ((*beamSpanElementCoords).at(i)->m_yBeam - verticalCenter < minDistToCenter)) {
                minDistToCenter = (*beamSpanElementCoords).at(i)->m_yBeam - verticalCenter;
            }
            else if ((this->m_stemDir == STEMDIRECTION_down)
                     && (verticalCenter - (*beamSpanElementCoords).at(i)->m_yBeam < minDistToCenter)) {
                minDistToCenter = verticalCenter - (*beamSpanElementCoords).at(i)->m_yBeam;
            }
        }
        minDistToCenter += (this->m_beamSpanWidthBlack / 2) + doc->GetDrawingUnit(staff->m_drawingStaffSize) / 4;
        if (minDistToCenter < 0) {
            this->m_startingY += (this->m_stemDir == STEMDIRECTION_down) ? minDistToCenter : -minDistToCenter;
            for (i = 0; i < elementCount; i++) {
                (*beamSpanElementCoords).at(i)->m_yBeam
                += (this->m_stemDir == STEMDIRECTION_down) ? minDistToCenter : -minDistToCenter;
            }
        }
        
        for (i = 0; i < elementCount; i++) {
            // All notes and chords get their stem value stored
            LayerElement *el = (*beamSpanElementCoords).at(i)->m_element;
            if ((el->Is(NOTE)) || (el->Is(CHORD))) {
                StemmedDrawingInterface *interface = el->GetStemmedDrawingInterface();
                assert(interface);
                
                if (this->m_stemDir == STEMDIRECTION_up) {
                    y1 = (*beamSpanElementCoords).at(i)->m_yBeam - doc->GetDrawingStemWidth(staff->m_drawingStaffSize);
                    y2 = (*beamSpanElementCoords).at(i)->m_yBottom
                    + interface->GetStemUpSE(doc, staff->m_drawingStaffSize, this->m_cueSize).y;
                }
                else {
                    y1 = (*beamSpanElementCoords).at(i)->m_yBeam + doc->GetDrawingStemWidth(staff->m_drawingStaffSize);
                    y2 = (*beamSpanElementCoords).at(i)->m_yTop
                    + interface->GetStemDownNW(doc, staff->m_drawingStaffSize, this->m_cueSize).y;
                }
                
                Stem *stem = interface->GetDrawingStem();
                // This is the case with fTrem on whole notes
                if (!stem) continue;
                
                stem->SetDrawingStemDir(this->m_stemDir);
                // Since the value were calculated relatively to the element position, adjust them
                stem->SetDrawingXRel((*beamSpanElementCoords).at(i)->m_x - el->GetDrawingX());
                stem->SetDrawingYRel(y2 - el->GetDrawingY());
                stem->SetDrawingStemLen(y2 - y1);
            }
        }
    }

    
    //----------------------------------------------------------------------------
    // BeamSpan
    //----------------------------------------------------------------------------
    
    BeamSpan::BeamSpan() : ControlElement("beamspan-"), ObjectListInterface(),TimeSpanningInterface(), AttColor(), AttPlacement(), AttPlist()
    {
        RegisterInterface(TimeSpanningInterface::GetAttClasses(), TimeSpanningInterface::IsInterface());
        RegisterAttClass(ATT_COLOR);
        RegisterAttClass(ATT_PLACEMENT);
        RegisterAttClass(ATT_PLIST);
        
        Reset();
    }
    
    BeamSpan::~BeamSpan()
    {
        ClearCoords();
    }
    
    void BeamSpan::Reset()
    {
        ControlElement::Reset();
        TimeSpanningInterface::Reset();
        ResetPlist();
        ResetColor();
        ResetPlacement();
        
        ClearCoords();
    }
    
    void BeamSpan::AddChild(Object *child)
    {
        if (child->Is(BEAM)) {
            assert(dynamic_cast<Beam *>(child));
        }
        else if (child->Is(CHORD)) {
            assert(dynamic_cast<Chord *>(child));
        }
        else if (child->Is(CLEF)) {
            assert(dynamic_cast<Clef *>(child));
        }
        else if (child->Is(NOTE)) {
            assert(dynamic_cast<Note *>(child));
        }
        else if (child->Is(REST)) {
            assert(dynamic_cast<Rest *>(child));
        }
        else if (child->Is(SPACE)) {
            assert(dynamic_cast<Space *>(child));
        }
        else if (child->Is(TUPLET)) {
            assert(dynamic_cast<Tuplet *>(child));
        }
        else if (child->IsEditorialElement()) {
            assert(dynamic_cast<EditorialElement *>(child));
        }
        else {
            LogError("Adding '%s' to a '%s'", child->GetClassName().c_str(), this->GetClassName().c_str());
            assert(false);
        }
        
        child->SetParent(this);
        m_children.push_back(child);
        Modify();
    }
    
    void BeamSpan::FilterList(ListOfObjects *childList)
    {
        bool firstNoteGrace = false;
        // We want to keep only notes and rests
        // Eventually, we also need to filter out grace notes properly (e.g., with sub-beams)
        ListOfObjects::iterator iter = childList->begin();
        
        while (iter != childList->end()) {
            if (!(*iter)->IsLayerElement()) {
                // remove anything that is not an LayerElement (e.g. Verse, Syl, etc)
                iter = childList->erase(iter);
                continue;
            }
            if (!(*iter)->HasInterface(INTERFACE_DURATION)) {
                // remove anything that has not a DurationInterface
                iter = childList->erase(iter);
                continue;
            }
            else {
                LayerElement *element = dynamic_cast<LayerElement *>(*iter);
                assert(element);
                // if we are at the beginning of the beam
                // and the note is cueSize
                // assume all the beam is of grace notes
                if (childList->begin() == iter) {
                    if (element->IsGraceNote()) firstNoteGrace = true;
                }
                // if the first note in beam was NOT a grace
                // we have grace notes embedded in a beam
                // drop them
                if (!firstNoteGrace && element->IsGraceNote()) {
                    iter = childList->erase(iter);
                    continue;
                }
                // also remove notes within chords
                if (element->Is(NOTE)) {
                    Note *note = dynamic_cast<Note *>(element);
                    assert(note);
                    if (note->IsChordTone()) {
                        iter = childList->erase(iter);
                        continue;
                    }
                }
                iter++;
            }
        }
        
        InitCoords(childList);
    }
    
    void BeamSpan::InitCoords(ListOfObjects *childList)
    {
        ClearCoords();
        
        if (childList->empty()) {
            return;
        }
        
        // duration variables
        int lastDur, currentDur;
        
        m_beamSpanElementCoords.reserve(childList->size());
        int i;
        for (i = 0; i < (int)childList->size(); i++) {
            m_beamSpanElementCoords.push_back(new BeamElementCoord());
        }
        
        // current point to the first Note in the layed out layer
        LayerElement *current = dynamic_cast<LayerElement *>(childList->front());
        // Beam list should contain only DurationInterface objects
        assert(current->GetDurationInterface());
        
        lastDur = (current->GetDurationInterface())->GetActualDur();
        
        /******************************************************************/
        // Populate BeamElementCoord for each element in the beam
        // This could be moved to Beam::InitCoord for optimization because there should be no
        // need for redoing it everytime it is drawn.
        
        data_STEMDIRECTION currentStemDir;
        
        int elementCount = 0;
        
        ListOfObjects::iterator iter = childList->begin();
        do {
            // Beam list should contain only DurationInterface objects
            assert(current->GetDurationInterface());
            currentDur = (current->GetDurationInterface())->GetActualDur();
            
            if (current->Is(CHORD)) {
                m_drawingParams.m_beamSpanHasChord = true;
            }
            
            m_beamSpanElementCoords.at(elementCount)->m_element = current;
            current->m_beamElementCoord = m_beamSpanElementCoords.at(elementCount);
            m_beamSpanElementCoords.at(elementCount)->m_dur = currentDur;
            
            // Look at beam breaks
            m_beamSpanElementCoords.at(elementCount)->m_breaksec = 0;
            AttBeamsecondary *beamsecondary = dynamic_cast<AttBeamsecondary *>(current);
            if (beamsecondary && beamsecondary->HasBreaksec()) {
                if (!m_drawingParams.m_changingDur) m_drawingParams.m_changingDur = true;
                m_beamSpanElementCoords.at(elementCount)->m_breaksec = beamsecondary->GetBreaksec();
            }
            
            // Skip rests
            if (current->Is({ NOTE, CHORD })) {
                // look at the stemDir to see if we have multiple stem Dir
                if (!m_drawingParams.m_hasMultipleStemDir) {
                    StemmedDrawingInterface *interface = current->GetStemmedDrawingInterface();
                    assert(interface);
                    Stem *stem = interface->GetDrawingStem();
                    currentStemDir = STEMDIRECTION_NONE;
                    if (stem) {
                        assert(dynamic_cast<AttStems *>(stem));
                        currentStemDir = (dynamic_cast<AttStems *>(stem))->GetStemDir();
                    }
                    if (currentStemDir != STEMDIRECTION_NONE) {
                        if ((m_drawingParams.m_stemDir != STEMDIRECTION_NONE)
                            && (m_drawingParams.m_stemDir != currentStemDir)) {
                            m_drawingParams.m_hasMultipleStemDir = true;
                        }
                        m_drawingParams.m_stemDir = currentStemDir;
                    }
                }
            }
            // keep the shortest dur in the beam
            m_drawingParams.m_shortestDur = std::max(currentDur, m_drawingParams.m_shortestDur);
            // check if we have more than duration in the beam
            if (!m_drawingParams.m_changingDur && currentDur != lastDur) m_drawingParams.m_changingDur = true;
            lastDur = currentDur;
            
            elementCount++;
            
            iter++;
            if (iter == childList->end()) {
                break;
            }
            current = dynamic_cast<LayerElement *>(*iter);
            if (current == NULL) {
                LogDebug("Error accessing element in Beam list");
                return;
            }
            
        } while (1);
        
        // elementCount must be greater than 0 here
        if (elementCount == 0) {
            LogDebug("Beam with no notes of duration > 8 detected. Exiting DrawBeam.");
            return;
        }
        
        int last = elementCount - 1;
        
        // We look only at the last note for checking if cue-sized. Somehow arbitrarily
        m_drawingParams.m_cueSize = m_beamSpanElementCoords.at(last)->m_element->IsCueSize();
    }
    
    void BeamSpan::ClearCoords()
    {
        ArrayOfBeamElementCoords::iterator iter;
        for (iter = m_beamSpanElementCoords.begin(); iter != m_beamSpanElementCoords.end(); ++iter) {
            delete *iter;
        }
        m_beamSpanElementCoords.clear();
    }
    
    //----------------------------------------------------------------------------
    // BeamSpanElementCoord
    //----------------------------------------------------------------------------
    
    
     BeamSpanElementCoord::~BeamSpanElementCoord()
     {
     if (m_element) m_element->m_beamElementCoord = NULL;
     }
    
    
    
    
} // namespace vrv
