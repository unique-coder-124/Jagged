<p align="center">
    <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" align="center" width="30%">
</p>
<p align="center"><h1 align="center">JAGGED</h1></p>
<p align="center">
	<em><code>A programming language thats rough around the edges... and everywhere else.</code></em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/license/unique-coder-124/Jagged?style=default&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
	<img src="https://img.shields.io/github/last-commit/unique-coder-124/Jagged?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/unique-coder-124/Jagged?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/unique-coder-124/Jagged?style=default&color=0080ff" alt="repo-language-count">
</p>
<p align="center"><!-- default option, no dependency badges. -->
</p>
<p align="center">
	<!-- default option, no dependency badges. -->
</p>
<br>

##  Table of Contents

- [ Overview](#-overview)
- [ Features](#-features)
- [ Project Structure](#-project-structure)
  - [ Project Index](#-project-index)
- [ Getting Started](#-getting-started)
  - [ Prerequisites](#-prerequisites)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
  - [ Testing](#-testing)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)

---

##  Overview

A random language i'm making to learn more about how compilers and interpreters work.
really dirty source code.

---

##  Features

just a tokenizer so far.
refer to the [Project Roadmap](#-project-roadmap) for info on feature i want to implement.

---

##  Project Structure

```sh
└── Jagged/
    ├── JaggedDLL
    │   ├── GLOBALS.h
    │   └── classes
    │       ├── ErrHandler.cpp
    │       ├── ErrHandler.h
    │       ├── tokenizer.cpp
    │       └── tokenizer.h
    ├── JaggedLang
    │   └── main.cpp
    ├── CMakeLists.txt
    ├── LICENSE.txt
    └── README.md
```


###  Project Index
<details open>
	<summary><b><code>JAGGED/</code></b></summary>
	<details> <!-- __root__ Submodule -->
		<summary><b>__root__</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/LICENSE.txt'>CMakeLists.txt</a></b></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/LICENSE.txt'>LICENSE.txt</a></b></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/LICENSE.txt'>Readme.md</a></b></td>
			</tr>
			</table>
		</blockquote>
	</details>
	<details> <!-- JaggedDLL Submodule -->
		<summary><b>JaggedDLL</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/JaggedDLL/GLOBALS.h'>GLOBALS.h</a></b></td>
			</tr>
			</table>
			<details>
				<summary><b>classes</b></summary>
				<blockquote>
					<table>
					<tr>
						<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/JaggedDLL/classes/ErrHandler.cpp'>ErrHandler.cpp</a></b></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/JaggedDLL/classes/tokenizer.h'>tokenizer.h</a></b></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/JaggedDLL/classes/tokenizer.cpp'>tokenizer.cpp</a></b></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/JaggedDLL/classes/ErrHandler.h'>ErrHandler.h</a></b></td>
					</tr>
					</table>
				</blockquote>
			</details>
		</blockquote>
	</details>
	<details> <!-- JaggedLang Submodule -->
		<summary><b>JaggedLang</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/unique-coder-124/Jagged/blob/master/JaggedLang/main.cpp'>main.cpp</a></b></td>
			</tr>
			</table>
		</blockquote>
	</details>
</details>

---
##  Getting Started

###  Prerequisites

Before getting started with Jagged, ensure your runtime environment meets the following requirements:

- **Programming Language:** C++


###  Installation

Install Jagged using one of the following methods:

**Build from source:**

1. Clone the Jagged repository:
```sh
❯ git clone https://github.com/unique-coder-124/Jagged.git
```

2. Navigate to the project directory:
```sh
❯ cd Jagged
```

3. Create build dir:
```sh
mkdir build
cd build
```

3. run cmake and make:
```sh
cmake ..
make
```
If on windows run:
```sh
cmake -G "Unix Makefiles" ..
make
```

**Download release:**

**CURENTLY UNAVAILABLE**




###  Usage
Run Jagged using the following command:
```sh
Jagged <command> <filename> <[optional] flags>
```
comands include:
```sh
tokenize
--help, -h
--version, -v
```
`parse` is technically a command right now but it has not yet been implemented

For help run: 
```
Jagged --help
```

##  Project Roadmap

- [X] **`Task 1`**: <strike>tokenizer.</strike>
- [ ] **`Task 2`**: parser.
- [ ] **`Task 3`**: interpreter.
- [ ] **`Task 4`**: transpiler. |to C++| |use C++ compiler g++|
- [ ] **`Task 5`**: file inludes/imports.
- [ ] **`Task 6`**: inlude/import C++ files.
- [ ] **`Task 7`**: compile to dll.
- [ ] **`Task 8`**: compiler. |to assembly directly|
- [ ] **`task 9`**: optimizer.
- [ ] **`task 9`**: rewrite in Jagged for Jaggedception

---

##  Contributing

- **💬 [Join the Discussions](https://github.com/unique-coder-124/Jagged/discussions)**: Share your insights, provide feedback, or ask questions.
- **🐛 [Report Issues](https://github.com/unique-coder-124/Jagged/issues)**: Submit bugs found or log feature requests for the `Jagged` project.
<!--
- **💡 [Submit Pull Requests](https://github.com/unique-coder-124/Jagged/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/unique-coder-124/Jagged/
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to github**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>
-->

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com{/unique-coder-124/Jagged/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=unique-coder-124/Jagged">
   </a>
</p>
</details>

---

##  License

This project is protected under the [APACHE 2.0](LICENSE.txt) License.

---
