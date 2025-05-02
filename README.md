# Plex: Scaling Parallel Lexing with Backtrack-Free Prescanning

This project is an implementation of a **parallel lexer generator** based on the research paper:

L. Li, S. Sato, Q. Liu and K. Taura, "Plex: Scaling Parallel Lexing with Backtrack-Free Prescanning," 2021 IEEE International Parallel and Distributed Processing Symposium (IPDPS), Portland, OR, USA, 2021, pp. 693-702, doi: 10.1109/IPDPS49936.2021.00079.

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
