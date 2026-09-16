# InfiniteScript Language Specification

## Philosophy

InfiniteScript is designed to give developers maximum freedom while
keeping common tasks dramatically simpler than traditional languages.

The language should not artificially restrict developers to a small
collection of built-in use cases.

Developers should be able to create:

- CLI applications
- Desktop applications
- Native Windows applications
- Games
- Tools
- Servers
- APIs
- Websites
- Developer tools
- Automation
- Data applications
- Graphics applications
- 2D applications
- 3D applications
- UI applications
- Libraries
- Packages
- Plugins
- Services

---

# Core Language

## Values

- Number
- Decimal
- Boolean
- String
- Character
- Null
- Array
- List
- Map
- Set
- Object
- Function

## Variables

Local
Set
Change
Constant

## Operators

Arithmetic:

+
-
*
/
%
**

Comparison:

==
>
<
>=
<=

Logical:

And
Or
Not

Bitwise:

&
|
^
~
<<
>>

Assignment:

=
+=
-=
*=
/=
%=

---

# Control Flow

If
Else If
Else
End

Switch
Case
Default

While
For
For Each

Break
Continue

Return

---

# Functions

Function
Return

Parameters
Default parameters
Named parameters
Optional parameters
Variadic parameters

Anonymous functions
Lambda functions

---

# Object System

Class
Object
Property
Method
Constructor

Extends
Implements

Public
Private
Protected

Static

Abstract

Interface

Enum

---

# Type System

Dynamic typing should remain simple.

Optional explicit typing should be available.

Developers should be able to create custom types.

Required features:

- Type declarations
- Type inference
- Type checking
- Type conversion
- Generic types
- Union types
- Nullable types
- Custom types

---

# Collections

Array
List
Map
Set

Operations:

Add
Remove
Clear
Contains
Find
Sort
Reverse
Length

---

# Errors

Try
Catch
Finally
Throw

Custom exceptions.

---

# Files

Read File
Write File
Append File
Delete File
Copy File
Move File

Directories.

File metadata.

---

# Data

JSON
CSV
Text
Binary

Serialization
Deserialization

---

# Networking

HTTP
HTTPS
TCP
UDP
WebSocket

Requests
Responses

Server
Route
Middleware

---

# Async

Async
Await
Task

Parallel execution.

Timers.

Background work.

---

# Packages

Package
Import
Export

Package manager.

Local packages.

Remote packages.

Versioning.

---

# Events

On
Event
Emit

Custom events.

Event arguments.

---

# Math

Random
Math functions
Trigonometry
Vectors
Matrices
Colors
Transforms

---

# Date and Time

Date
Time
DateTime
Duration
Timezone

---

# Processes

Start Process
Stop Process
Arguments
Environment variables

---

# Reflection

Inspect types.

Inspect properties.

Inspect methods.

Inspect functions.

Runtime metadata.

---

# Native Integration

InfiniteScript must allow access to native functionality when required.

Developers should be able to use:

- Native Windows APIs
- DLLs
- Native libraries
- System processes
- Filesystem
- Devices
- Networking
- Graphics APIs

The language should not artificially prevent advanced developers
from extending the runtime.

---

# Infinite UI

UI
Window
Container
Row
Column
Stack
Grid
Scroll
Spacer
Padding
Margin

Text
Button
TextBox
PasswordBox
CheckBox
RadioButton
Toggle
Slider
ProgressBar
Dropdown
List
Table
Tree
TabView
Menu
MenuItem

Image
Icon
Card
Panel
Border
Divider
Badge
Avatar

Gradient
Shadow
Blur
Opacity
CornerRadius

Font
FontSize
FontWeight
Color

---

# UI Events

Click
DoubleClick
Hover
Press
Release
Focus
Blur
Change
Submit
Select
Drag
Drop
KeyDown
KeyUp
Scroll
Resize

---

# Windows

Modal
Dialog
Popup
Notification
Tooltip
ContextMenu
Sidebar
Toolbar
StatusBar

---

# Animation

Animate
Duration
Delay
Easing
From
To

Sequence
Parallel
Repeat

Spring

Timeline
Keyframe

---

# Graphics

2D drawing.

Shapes.

Sprites.

Textures.

Canvas.

Shaders.

Particles.

---

# 3D

Scene
Camera
Model
Mesh
Material
Texture
Light

Directional
Point
Spot

Transform
Position
Rotation
Scale

Physics.

Collision.

---

# Developer Tools

CLI
REPL
Debugger
Formatter
Test runner
Package manager
Documentation generator
Project generator
Profiler
AST inspector
Token inspector

---

# CLI

Inf help
Inf version
Inf run
Inf check
Inf build
Inf new
Inf init
Inf clean

Planned:

Inf test
Inf format
Inf repl
Inf inspect
Inf docs

Inf package install
Inf package remove
Inf package update
Inf package list
Inf package search

Inf build debug
Inf build release

Inf run watch

---

# Extensibility

InfiniteScript should support user-created:

- Functions
- Classes
- Types
- Packages
- UI components
- Events
- Animations
- Libraries
- Plugins
- Native extensions

The standard library should provide useful defaults without becoming
a restriction on what developers can build.

---

# Version Targets

v0.3
Core language expansion.

v0.4
Object system.

v0.5
Advanced runtime.

v0.6
Infinite UI.

v0.7
Animation and graphics.

v0.8
Networking and services.

v0.9
Compiler and developer tooling.

v1.0
Stable language specification.

Post-1.0:
The language remains extensible rather than frozen.
