/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2015 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::Regulator

Description
    Regulator is a class which allows user to read value of a specified
    scalar field in some location inside mesh and returns a value between
    -1.0 and 1.0. Returned value dependent on the regulator settings
    obtained from "regulatorProperties" inside the "constant" directory.

    regulatorProperties dict:
    \table
        Property        | Description                 | Required |
        patchName       | name of measurement patch   | yes      |
        fieldName       | measured field name         | yes       |
        targetValue     | desired value               | yes      |
        Kp              | proportional gain           | yes      |
        Ti              | integral gain               | yes      |
        Td              | differential gain           | yes      |
    \endtable

\*---------------------------------------------------------------------------*/

#ifndef Regulator_H
#define Regulator_H

#include "fvCFD.H"
#include "sensor.H"
#include "controlMethod.H"


class Regulator
{
public:
    Regulator() = delete;
    ~Regulator();

    // Initialize from mesh and dictionary form "constant" directory
    Regulator(const fvMesh &mesh, const dictionary &dict);

    // Initialize from mesh and default dictionary
    Regulator(const fvMesh &mesh);

    scalar targetValue() const { return targetValue_; }

    //- Read output signal from the regulator
    scalar read();

    //- Write to runtime dict
    void write(Ostream& os, const word dictName = "regulator") const;

private:
    const fvMesh &mesh_;            // Reference to the system mesh
    const Sensor* sensor_;          // Sensor instance for reading field values
    ControlMethod* controlMethod_;  // Control algorithm
    scalar targetValue_;            // Reference value used by the control loop
    label timeIndex_;               // Time index of the last update
};

#endif