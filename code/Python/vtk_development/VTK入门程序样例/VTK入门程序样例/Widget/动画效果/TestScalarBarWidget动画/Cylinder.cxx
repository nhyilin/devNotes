/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestScalarBarWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPLOT3DReader.h"
#include "vtkScalarBarWidget.h"
#include "vtkStructuredGridGeometryFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkScalarBarActor.h"
#include "vtkStructuredGrid.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

char TSBWeventLog[] =
"# StreamVersion 1\n"
"CharEvent 153 168 0 0 105 1 i\n"
"KeyReleaseEvent 153 168 0 0 105 1 i\n"
"MouseMoveEvent 153 167 0 0 0 0 i\n"
"MouseMoveEvent 154 166 0 0 0 0 i\n"
"MouseMoveEvent 156 165 0 0 0 0 i\n"
"MouseMoveEvent 159 163 0 0 0 0 i\n"
"MouseMoveEvent 163 162 0 0 0 0 i\n"
"MouseMoveEvent 167 161 0 0 0 0 i\n"
"MouseMoveEvent 170 161 0 0 0 0 i\n"
"MouseMoveEvent 172 161 0 0 0 0 i\n"
"MouseMoveEvent 173 161 0 0 0 0 i\n"
"MouseMoveEvent 176 161 0 0 0 0 i\n"
"MouseMoveEvent 179 161 0 0 0 0 i\n"
"MouseMoveEvent 181 161 0 0 0 0 i\n"
"MouseMoveEvent 185 160 0 0 0 0 i\n"
"MouseMoveEvent 188 159 0 0 0 0 i\n"
"MouseMoveEvent 191 159 0 0 0 0 i\n"
"MouseMoveEvent 195 158 0 0 0 0 i\n"
"MouseMoveEvent 198 157 0 0 0 0 i\n"
"MouseMoveEvent 201 157 0 0 0 0 i\n"
"MouseMoveEvent 203 157 0 0 0 0 i\n"
"MouseMoveEvent 205 157 0 0 0 0 i\n"
"MouseMoveEvent 208 156 0 0 0 0 i\n"
"MouseMoveEvent 212 156 0 0 0 0 i\n"
"MouseMoveEvent 217 155 0 0 0 0 i\n"
"MouseMoveEvent 220 155 0 0 0 0 i\n"
"MouseMoveEvent 222 155 0 0 0 0 i\n"
"MouseMoveEvent 224 154 0 0 0 0 i\n"
"MouseMoveEvent 227 154 0 0 0 0 i\n"
"MouseMoveEvent 230 154 0 0 0 0 i\n"
"MouseMoveEvent 234 153 0 0 0 0 i\n"
"MouseMoveEvent 237 153 0 0 0 0 i\n"
"MouseMoveEvent 239 153 0 0 0 0 i\n"
"MouseMoveEvent 240 153 0 0 0 0 i\n"
"MouseMoveEvent 242 153 0 0 0 0 i\n"
"MouseMoveEvent 243 153 0 0 0 0 i\n"
"MouseMoveEvent 245 153 0 0 0 0 i\n"
"MouseMoveEvent 246 153 0 0 0 0 i\n"
"MouseMoveEvent 247 152 0 0 0 0 i\n"
"MouseMoveEvent 248 152 0 0 0 0 i\n"
"MouseMoveEvent 249 152 0 0 0 0 i\n"
"MouseMoveEvent 250 152 0 0 0 0 i\n"
"MouseMoveEvent 251 152 0 0 0 0 i\n"
"MouseMoveEvent 252 152 0 0 0 0 i\n"
"MouseMoveEvent 253 152 0 0 0 0 i\n"
"MouseMoveEvent 253 151 0 0 0 0 i\n"
"MouseMoveEvent 254 151 0 0 0 0 i\n"
"LeftButtonPressEvent 254 151 0 0 0 0 i\n"
"MouseMoveEvent 253 150 0 0 0 0 i\n"
"MouseMoveEvent 251 148 0 0 0 0 i\n"
"MouseMoveEvent 248 145 0 0 0 0 i\n"
"MouseMoveEvent 243 141 0 0 0 0 i\n"
"MouseMoveEvent 240 137 0 0 0 0 i\n"
"MouseMoveEvent 236 133 0 0 0 0 i\n"
"MouseMoveEvent 234 130 0 0 0 0 i\n"
"MouseMoveEvent 232 128 0 0 0 0 i\n"
"MouseMoveEvent 229 125 0 0 0 0 i\n"
"MouseMoveEvent 226 122 0 0 0 0 i\n"
"MouseMoveEvent 222 118 0 0 0 0 i\n"
"MouseMoveEvent 219 115 0 0 0 0 i\n"
"MouseMoveEvent 217 112 0 0 0 0 i\n"
"MouseMoveEvent 215 110 0 0 0 0 i\n"
"MouseMoveEvent 212 107 0 0 0 0 i\n"
"MouseMoveEvent 210 103 0 0 0 0 i\n"
"MouseMoveEvent 207 100 0 0 0 0 i\n"
"MouseMoveEvent 203 96 0 0 0 0 i\n"
"MouseMoveEvent 199 94 0 0 0 0 i\n"
"MouseMoveEvent 196 91 0 0 0 0 i\n"
"MouseMoveEvent 193 88 0 0 0 0 i\n"
"MouseMoveEvent 191 86 0 0 0 0 i\n"
"MouseMoveEvent 188 83 0 0 0 0 i\n"
"MouseMoveEvent 186 80 0 0 0 0 i\n"
"MouseMoveEvent 182 78 0 0 0 0 i\n"
"MouseMoveEvent 179 75 0 0 0 0 i\n"
"MouseMoveEvent 175 73 0 0 0 0 i\n"
"MouseMoveEvent 172 70 0 0 0 0 i\n"
"MouseMoveEvent 169 68 0 0 0 0 i\n"
"MouseMoveEvent 167 65 0 0 0 0 i\n"
"MouseMoveEvent 164 63 0 0 0 0 i\n"
"MouseMoveEvent 162 60 0 0 0 0 i\n"
"MouseMoveEvent 160 58 0 0 0 0 i\n"
"MouseMoveEvent 157 56 0 0 0 0 i\n"
"MouseMoveEvent 155 55 0 0 0 0 i\n"
"MouseMoveEvent 153 53 0 0 0 0 i\n"
"MouseMoveEvent 151 51 0 0 0 0 i\n"
"MouseMoveEvent 149 49 0 0 0 0 i\n"
"MouseMoveEvent 148 47 0 0 0 0 i\n"
"MouseMoveEvent 147 46 0 0 0 0 i\n"
"MouseMoveEvent 145 44 0 0 0 0 i\n"
"MouseMoveEvent 143 41 0 0 0 0 i\n"
"MouseMoveEvent 142 40 0 0 0 0 i\n"
"MouseMoveEvent 141 40 0 0 0 0 i\n"
"MouseMoveEvent 140 39 0 0 0 0 i\n"
"MouseMoveEvent 139 37 0 0 0 0 i\n"
"MouseMoveEvent 138 36 0 0 0 0 i\n"
"MouseMoveEvent 138 35 0 0 0 0 i\n"
"MouseMoveEvent 137 35 0 0 0 0 i\n"
"MouseMoveEvent 136 34 0 0 0 0 i\n"
"MouseMoveEvent 135 32 0 0 0 0 i\n"
"MouseMoveEvent 134 32 0 0 0 0 i\n"
"MouseMoveEvent 134 33 0 0 0 0 i\n"
"MouseMoveEvent 132 34 0 0 0 0 i\n"
"MouseMoveEvent 131 37 0 0 0 0 i\n"
"MouseMoveEvent 129 40 0 0 0 0 i\n"
"MouseMoveEvent 127 44 0 0 0 0 i\n"
"MouseMoveEvent 126 49 0 0 0 0 i\n"
"MouseMoveEvent 123 53 0 0 0 0 i\n"
"MouseMoveEvent 121 56 0 0 0 0 i\n"
"MouseMoveEvent 118 60 0 0 0 0 i\n"
"MouseMoveEvent 115 63 0 0 0 0 i\n"
"MouseMoveEvent 112 66 0 0 0 0 i\n"
"MouseMoveEvent 110 68 0 0 0 0 i\n"
"MouseMoveEvent 108 71 0 0 0 0 i\n"
"MouseMoveEvent 105 73 0 0 0 0 i\n"
"MouseMoveEvent 102 75 0 0 0 0 i\n"
"MouseMoveEvent 99 78 0 0 0 0 i\n"
"MouseMoveEvent 96 80 0 0 0 0 i\n"
"MouseMoveEvent 93 83 0 0 0 0 i\n"
"MouseMoveEvent 91 85 0 0 0 0 i\n"
"MouseMoveEvent 88 87 0 0 0 0 i\n"
"MouseMoveEvent 85 90 0 0 0 0 i\n"
"MouseMoveEvent 82 93 0 0 0 0 i\n"
"MouseMoveEvent 79 95 0 0 0 0 i\n"
"MouseMoveEvent 76 96 0 0 0 0 i\n"
"MouseMoveEvent 73 97 0 0 0 0 i\n"
"MouseMoveEvent 70 99 0 0 0 0 i\n"
"MouseMoveEvent 67 101 0 0 0 0 i\n"
"MouseMoveEvent 64 102 0 0 0 0 i\n"
"MouseMoveEvent 62 104 0 0 0 0 i\n"
"MouseMoveEvent 58 105 0 0 0 0 i\n"
"MouseMoveEvent 54 105 0 0 0 0 i\n"
"MouseMoveEvent 51 106 0 0 0 0 i\n"
"MouseMoveEvent 47 107 0 0 0 0 i\n"
"MouseMoveEvent 45 109 0 0 0 0 i\n"
"MouseMoveEvent 44 110 0 0 0 0 i\n"
"MouseMoveEvent 43 112 0 0 0 0 i\n"
"MouseMoveEvent 41 113 0 0 0 0 i\n"
"MouseMoveEvent 40 115 0 0 0 0 i\n"
"MouseMoveEvent 39 117 0 0 0 0 i\n"
"MouseMoveEvent 38 119 0 0 0 0 i\n"
"MouseMoveEvent 38 120 0 0 0 0 i\n"
"MouseMoveEvent 38 123 0 0 0 0 i\n"
"MouseMoveEvent 38 125 0 0 0 0 i\n"
"MouseMoveEvent 38 128 0 0 0 0 i\n"
"MouseMoveEvent 38 129 0 0 0 0 i\n"
"MouseMoveEvent 37 131 0 0 0 0 i\n"
"MouseMoveEvent 36 132 0 0 0 0 i\n"
"MouseMoveEvent 35 133 0 0 0 0 i\n"
"MouseMoveEvent 34 134 0 0 0 0 i\n"
"MouseMoveEvent 33 134 0 0 0 0 i\n"
"MouseMoveEvent 31 134 0 0 0 0 i\n"
"MouseMoveEvent 30 134 0 0 0 0 i\n"
"MouseMoveEvent 29 134 0 0 0 0 i\n"
"MouseMoveEvent 28 135 0 0 0 0 i\n"
"MouseMoveEvent 26 136 0 0 0 0 i\n"
"MouseMoveEvent 24 137 0 0 0 0 i\n"
"MouseMoveEvent 23 140 0 0 0 0 i\n"
"MouseMoveEvent 22 141 0 0 0 0 i\n"
"MouseMoveEvent 21 142 0 0 0 0 i\n"
"MouseMoveEvent 21 143 0 0 0 0 i\n"
"MouseMoveEvent 21 144 0 0 0 0 i\n"
"MouseMoveEvent 20 145 0 0 0 0 i\n"
"MouseMoveEvent 19 146 0 0 0 0 i\n"
"MouseMoveEvent 19 148 0 0 0 0 i\n"
"MouseMoveEvent 19 149 0 0 0 0 i\n"
"MouseMoveEvent 19 150 0 0 0 0 i\n"
"MouseMoveEvent 19 151 0 0 0 0 i\n"
"MouseMoveEvent 19 152 0 0 0 0 i\n"
"MouseMoveEvent 19 153 0 0 0 0 i\n"
"MouseMoveEvent 18 154 0 0 0 0 i\n"
"MouseMoveEvent 18 155 0 0 0 0 i\n"
"MouseMoveEvent 18 156 0 0 0 0 i\n"
"MouseMoveEvent 18 157 0 0 0 0 i\n"
"MouseMoveEvent 18 158 0 0 0 0 i\n"
"MouseMoveEvent 18 159 0 0 0 0 i\n"
"MouseMoveEvent 19 160 0 0 0 0 i\n"
"MouseMoveEvent 19 161 0 0 0 0 i\n"
"MouseMoveEvent 19 162 0 0 0 0 i\n"
"MouseMoveEvent 19 163 0 0 0 0 i\n"
"MouseMoveEvent 24 165 0 0 0 0 i\n"
"MouseMoveEvent 40 168 0 0 0 0 i\n"
"MouseMoveEvent 58 170 0 0 0 0 i\n"
"MouseMoveEvent 62 171 0 0 0 0 i\n"
"MouseMoveEvent 76 174 0 0 0 0 i\n"
"MouseMoveEvent 80 176 0 0 0 0 i\n"
"MouseMoveEvent 84 178 0 0 0 0 i\n"
"MouseMoveEvent 88 179 0 0 0 0 i\n"
"MouseMoveEvent 90 181 0 0 0 0 i\n"
"MouseMoveEvent 92 182 0 0 0 0 i\n"
"MouseMoveEvent 95 183 0 0 0 0 i\n"
"MouseMoveEvent 100 186 0 0 0 0 i\n"
"MouseMoveEvent 103 188 0 0 0 0 i\n"
"MouseMoveEvent 106 190 0 0 0 0 i\n"
"MouseMoveEvent 109 192 0 0 0 0 i\n"
"MouseMoveEvent 112 194 0 0 0 0 i\n"
"MouseMoveEvent 114 196 0 0 0 0 i\n"
"MouseMoveEvent 118 199 0 0 0 0 i\n"
"MouseMoveEvent 122 202 0 0 0 0 i\n"
"MouseMoveEvent 125 206 0 0 0 0 i\n"
"MouseMoveEvent 127 208 0 0 0 0 i\n"
"MouseMoveEvent 128 210 0 0 0 0 i\n"
"MouseMoveEvent 129 212 0 0 0 0 i\n"
"MouseMoveEvent 131 214 0 0 0 0 i\n"
"MouseMoveEvent 133 217 0 0 0 0 i\n"
"MouseMoveEvent 134 219 0 0 0 0 i\n"
"MouseMoveEvent 135 221 0 0 0 0 i\n"
"MouseMoveEvent 136 223 0 0 0 0 i\n"
"MouseMoveEvent 137 225 0 0 0 0 i\n"
"MouseMoveEvent 137 227 0 0 0 0 i\n"
"MouseMoveEvent 137 230 0 0 0 0 i\n"
"MouseMoveEvent 137 231 0 0 0 0 i\n"
"MouseMoveEvent 138 233 0 0 0 0 i\n"
"MouseMoveEvent 138 234 0 0 0 0 i\n"
"MouseMoveEvent 138 235 0 0 0 0 i\n"
"MouseMoveEvent 138 236 0 0 0 0 i\n"
"MouseMoveEvent 138 238 0 0 0 0 i\n"
"MouseMoveEvent 138 239 0 0 0 0 i\n"
"MouseMoveEvent 138 241 0 0 0 0 i\n"
"MouseMoveEvent 138 243 0 0 0 0 i\n"
"MouseMoveEvent 139 245 0 0 0 0 i\n"
"MouseMoveEvent 138 247 0 0 0 0 i\n"
"MouseMoveEvent 138 248 0 0 0 0 i\n"
"MouseMoveEvent 138 249 0 0 0 0 i\n"
"MouseMoveEvent 138 250 0 0 0 0 i\n"
"MouseMoveEvent 137 252 0 0 0 0 i\n"
"MouseMoveEvent 136 254 0 0 0 0 i\n"
"MouseMoveEvent 136 255 0 0 0 0 i\n"
"MouseMoveEvent 135 256 0 0 0 0 i\n"
"MouseMoveEvent 135 257 0 0 0 0 i\n"
"MouseMoveEvent 135 258 0 0 0 0 i\n"
"MouseMoveEvent 135 259 0 0 0 0 i\n"
"MouseMoveEvent 135 260 0 0 0 0 i\n"
"MouseMoveEvent 136 262 0 0 0 0 i\n"
"MouseMoveEvent 136 263 0 0 0 0 i\n"
"MouseMoveEvent 136 264 0 0 0 0 i\n"
"MouseMoveEvent 136 265 0 0 0 0 i\n"
"MouseMoveEvent 137 266 0 0 0 0 i\n"
"MouseMoveEvent 138 267 0 0 0 0 i\n"
"MouseMoveEvent 139 267 0 0 0 0 i\n"
"MouseMoveEvent 140 268 0 0 0 0 i\n"
"MouseMoveEvent 140 269 0 0 0 0 i\n"
"LeftButtonReleaseEvent 140 269 0 0 0 0 i\n"
"MouseMoveEvent 140 269 0 0 0 0 i\n"
"MouseMoveEvent 139 269 0 0 0 0 i\n"
"MouseMoveEvent 136 268 0 0 0 0 i\n"
"MouseMoveEvent 131 268 0 0 0 0 i\n"
"MouseMoveEvent 127 267 0 0 0 0 i\n"
"MouseMoveEvent 113 266 0 0 0 0 i\n"
"MouseMoveEvent 97 263 0 0 0 0 i\n"
"MouseMoveEvent 79 260 0 0 0 0 i\n"
"MouseMoveEvent 65 258 0 0 0 0 i\n"
"MouseMoveEvent 63 258 0 0 0 0 i\n"
"MouseMoveEvent 60 257 0 0 0 0 i\n"
"MouseMoveEvent 58 257 0 0 0 0 i\n"
"MouseMoveEvent 56 256 0 0 0 0 i\n"
"MouseMoveEvent 53 255 0 0 0 0 i\n"
"MouseMoveEvent 49 254 0 0 0 0 i\n"
"MouseMoveEvent 45 252 0 0 0 0 i\n"
"MouseMoveEvent 41 251 0 0 0 0 i\n"
"MouseMoveEvent 38 250 0 0 0 0 i\n"
"MouseMoveEvent 36 250 0 0 0 0 i\n"
"MouseMoveEvent 34 250 0 0 0 0 i\n"
"MouseMoveEvent 33 249 0 0 0 0 i\n"
"MouseMoveEvent 31 249 0 0 0 0 i\n"
"MouseMoveEvent 30 249 0 0 0 0 i\n"
"MouseMoveEvent 30 248 0 0 0 0 i\n"
"MouseMoveEvent 29 248 0 0 0 0 i\n"
"MouseMoveEvent 28 248 0 0 0 0 i\n"
"MouseMoveEvent 27 248 0 0 0 0 i\n"
"MouseMoveEvent 27 249 0 0 0 0 i\n"
"MouseMoveEvent 28 250 0 0 0 0 i\n"
"MouseMoveEvent 29 250 0 0 0 0 i\n"
"MouseMoveEvent 30 250 0 0 0 0 i\n"
"MouseMoveEvent 30 251 0 0 0 0 i\n"
"MouseMoveEvent 30 252 0 0 0 0 i\n"
"MouseMoveEvent 31 252 0 0 0 0 i\n"
"MouseMoveEvent 32 252 0 0 0 0 i\n"
"MouseMoveEvent 33 253 0 0 0 0 i\n"
"MouseMoveEvent 34 253 0 0 0 0 i\n"
"MouseMoveEvent 35 253 0 0 0 0 i\n"
"MouseMoveEvent 36 253 0 0 0 0 i\n"
"MouseMoveEvent 37 253 0 0 0 0 i\n"
"MouseMoveEvent 38 253 0 0 0 0 i\n"
"LeftButtonPressEvent 38 253 0 0 0 0 i\n"
"MouseMoveEvent 41 254 0 0 0 0 i\n"
"MouseMoveEvent 55 255 0 0 0 0 i\n"
"MouseMoveEvent 75 257 0 0 0 0 i\n"
"MouseMoveEvent 91 259 0 0 0 0 i\n"
"MouseMoveEvent 96 260 0 0 0 0 i\n"
"MouseMoveEvent 97 260 0 0 0 0 i\n"
"MouseMoveEvent 98 260 0 0 0 0 i\n"
"MouseMoveEvent 99 260 0 0 0 0 i\n"
"MouseMoveEvent 101 260 0 0 0 0 i\n"
"MouseMoveEvent 102 260 0 0 0 0 i\n"
"MouseMoveEvent 104 260 0 0 0 0 i\n"
"MouseMoveEvent 107 260 0 0 0 0 i\n"
"MouseMoveEvent 111 260 0 0 0 0 i\n"
"MouseMoveEvent 114 261 0 0 0 0 i\n"
"MouseMoveEvent 116 261 0 0 0 0 i\n"
"MouseMoveEvent 118 260 0 0 0 0 i\n"
"MouseMoveEvent 120 259 0 0 0 0 i\n"
"MouseMoveEvent 122 259 0 0 0 0 i\n"
"MouseMoveEvent 124 259 0 0 0 0 i\n"
"MouseMoveEvent 126 259 0 0 0 0 i\n"
"MouseMoveEvent 127 259 0 0 0 0 i\n"
"MouseMoveEvent 128 258 0 0 0 0 i\n"
"MouseMoveEvent 130 258 0 0 0 0 i\n"
"MouseMoveEvent 132 258 0 0 0 0 i\n"
"MouseMoveEvent 133 258 0 0 0 0 i\n"
"MouseMoveEvent 134 258 0 0 0 0 i\n"
"MouseMoveEvent 135 258 0 0 0 0 i\n"
"MouseMoveEvent 136 258 0 0 0 0 i\n"
"MouseMoveEvent 137 258 0 0 0 0 i\n"
"MouseMoveEvent 138 258 0 0 0 0 i\n"
"MouseMoveEvent 139 258 0 0 0 0 i\n"
"LeftButtonReleaseEvent 139 258 0 0 0 0 i\n"
"MouseMoveEvent 139 258 0 0 0 0 i\n"
"MouseMoveEvent 138 258 0 0 0 0 i\n"
"MouseMoveEvent 136 256 0 0 0 0 i\n"
"MouseMoveEvent 135 255 0 0 0 0 i\n"
"MouseMoveEvent 134 255 0 0 0 0 i\n"
"MouseMoveEvent 134 253 0 0 0 0 i\n"
"MouseMoveEvent 133 253 0 0 0 0 i\n"
"MouseMoveEvent 132 252 0 0 0 0 i\n"
"MouseMoveEvent 130 251 0 0 0 0 i\n"
"MouseMoveEvent 128 250 0 0 0 0 i\n"
"MouseMoveEvent 126 249 0 0 0 0 i\n"
"MouseMoveEvent 124 249 0 0 0 0 i\n"
"MouseMoveEvent 124 248 0 0 0 0 i\n"
"MouseMoveEvent 123 248 0 0 0 0 i\n"
"MouseMoveEvent 122 247 0 0 0 0 i\n"
"MouseMoveEvent 121 246 0 0 0 0 i\n"
"MouseMoveEvent 121 245 0 0 0 0 i\n"
"MouseMoveEvent 120 244 0 0 0 0 i\n"
"KeyPressEvent 120 244 0 0 105 1 i\n"
;

int main( int argc, char *argv[] )
{
 
  // Start by loading some data.
  vtkPLOT3DReader *pl3d = vtkPLOT3DReader::New();
  pl3d->SetXYZFileName("combxyz.bin");
  pl3d->SetQFileName("combq.bin");
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();
  
  // An outline is shown for context.
  vtkStructuredGridGeometryFilter *outline = 
    vtkStructuredGridGeometryFilter::New();
  outline->SetInputConnection(pl3d->GetOutputPort());
  outline->SetExtent(0,100,0,100,9,9);
  
  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkActor *outlineActor = vtkActor::New();
  outlineActor->SetMapper(outlineMapper);

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  vtkScalarBarWidget *scalarWidget = vtkScalarBarWidget::New();
  scalarWidget->SetInteractor(iren);
  scalarWidget->GetScalarBarActor()->SetTitle("Temperature");
  scalarWidget->GetScalarBarActor()->SetLookupTable(outlineMapper->GetLookupTable());
  
  ren1->AddActor(outlineActor);

  // Add the actors to the renderer, set the background and size
  //
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  // record events
  vtkInteractorEventRecorder *recorder = vtkInteractorEventRecorder::New();
  recorder->SetInteractor(iren);
//  recorder->SetFileName("c:/record.log");
//  recorder->Record();
  recorder->ReadFromInputStringOn();
  recorder->SetInputString(TSBWeventLog);

  // render the image
  iren->Initialize();
  renWin->Render();
  //scalarWidget->EnabledOn();
  recorder->Play();
  //recorder->EnabledOn();
  
  // Remove the observers so we can go interactive. Without this the "-I"
  // testing option fails.
  recorder->Off();

  int retVal = vtkRegressionTestImage( renWin );
  if ( retVal == vtkRegressionTester::DO_INTERACTOR)
    {
    iren->Start();
    }
  
  recorder->Off();
  recorder->Delete();
  scalarWidget->Delete();
  pl3d->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  
  return !retVal;
}
