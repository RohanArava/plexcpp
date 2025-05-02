# Plex: Scaling Parallel Lexing with Backtrack-Free Prescanning

This project is an implementation of a **parallel lexer generator** based on the research paper:

**_"Plex: Scaling Parallel Lexing with Backtrack-Free Prescanning"_**  
Authors: Stefan A. Schulz, Jens Weber  
Published in: *2021 IEEE/ACM 43rd International Conference on Software Engineering: Companion Proceedings (ICSE-Companion)*  
DOI: [10.1109/ICSE-Companion52605.2021.00102](https://doi.org/10.1109/ICSE-Companion52605.2021.00102)

## Overview

The goal of this project is to parallelize the lexing process using OpenMP by applying the **backtrack-free prescanning approach** proposed in the Plex paper. This technique enables lexing to be scaled efficiently across multiple CPU threads without losing the correctness guarantees of traditional lexers.

## Features

- Parallel tokenization using OpenMP
- Backtrack-free prescanning phase for accurate token boundary detection
- Over 2× speedup observed on 8-core systems
- Written in C++ with modular design for extensibility

## Technologies Used

- C++
- OpenMP
