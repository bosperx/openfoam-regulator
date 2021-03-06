/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
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
    Foam::regulatedGradientFvPatchScalarField

Group
    grpInletBoundaryConditions grpOutletBoundaryConditions

Description
    This boundary condition provides a regulated gradient, which is dependend
    of the Regulator signal in the linear manner.

    The gradient is set accoring to formula:

        (maxValue - minValue) * regulator_signal + minValue

Usage
    \table
        Property     | Description                          | Required | Default
        maxValue     | reference gradient for signal = 1    | yes |
        minValue     | reference gradient for signal = 0    | yes |
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            regulatedGradient;
        maxValue        10;
        minValue        0;
    }
    \endverbatim

\*---------------------------------------------------------------------------*/

#ifndef regulatedGradientFvPatchScalarField_H
#define regulatedGradientFvPatchScalarField_H

#include "fixedGradientFvPatchFields.H"
#include "regulator.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
             Class regulatedGradientFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class regulatedGradientFvPatchScalarField
:
    public fixedGradientFvPatchScalarField
{
    Regulator regulator_;
    scalar minValue_;
    scalar maxValue_;

public:

    //- Runtime type information
    TypeName("regulatedGradient");


    // Constructors

        //- Construct from patch and internal field
        regulatedGradientFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        regulatedGradientFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given regulatedGradientFvPatchScalarField
        //  onto a new patch
        regulatedGradientFvPatchScalarField
        (
            const regulatedGradientFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        regulatedGradientFvPatchScalarField
        (
            const regulatedGradientFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new regulatedGradientFvPatchScalarField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        regulatedGradientFvPatchScalarField
        (
            const regulatedGradientFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new regulatedGradientFvPatchScalarField(*this, iF)
            );
        }

        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
