const vscode = require("vscode");
const cp = require("child_process");
const fs = require("fs");
const path = require("path");

let diagnosticCollection;

const keywords = [
    "Say", "Set", "Change",
    "If", "Else", "Else If", "End",
    "While", "For", "Break", "Continue",
    "Function", "Local Function", "Return",
    "Input", "Random", "Local Storage",
    "UI", "Window", "Button", "Text", "Title", "Size",
    "On", "Click",
    "Package", "Import", "Export"
];

const documentation = {
    "Say": "Outputs text to the InfiniteScript console.",
    "Set": "Sets a variable to a value.",
    "Change": "Changes a numeric variable by an amount.",
    "If": "Starts a conditional block.",
    "Else": "Runs when the previous condition is false.",
    "Else If": "Tests another condition.",
    "End": "Ends a block.",
    "While": "Repeats a block while a condition is true.",
    "For": "Runs a counted loop.",
    "Break": "Stops the current loop.",
    "Continue": "Skips to the next loop iteration.",
    "Function": "Declares a function.",
    "Local Function": "Declares a local function.",
    "Return": "Returns a value from a function.",
    "Input": "Reads input from the user.",
    "Random": "Generates a random number.",
    "Local Storage": "Creates local program storage.",
    "UI": "Starts an InfiniteScript UI definition.",
    "Window": "Creates a UI window.",
    "Button": "Creates a UI button.",
    "Text": "Creates UI text.",
    "Title": "Sets a UI window title.",
    "Size": "Sets the size of a UI window.",
    "Package": "Declares an InfiniteScript package.",
    "Import": "Imports an InfiniteScript package.",
    "Export": "Exports an InfiniteScript symbol."
};

/* =========================================================
   InfiniteScript executable
   ========================================================= */

function findInfiniteScript(workspaceRoot) {
    let current = workspaceRoot;

    for (let i = 0; i < 6 && current; i++) {

        const candidates = [
            path.join(current, "Inf.exe"),
            path.join(current, "Inf"),
            path.join(current, "Info", "Inf.exe"),
            path.join(current, "Info", "Inf"),
            path.join(current, "build", "Inf.exe"),
            path.join(current, "dist", "Inf.exe")
        ];

        for (const candidate of candidates) {
            if (fs.existsSync(candidate)) {
                return candidate;
            }
        }

        const parent = path.dirname(current);

        if (parent === current) {
            break;
        }

        current = parent;
    }

    return null;
}

function getWorkspaceRoot() {
    const folders = vscode.workspace.workspaceFolders;

    if (!folders || folders.length === 0) {
        return null;
    }

    return folders[0].uri.fsPath;
}

function getCurrentFile() {
    const editor = vscode.window.activeTextEditor;

    if (!editor) {
        vscode.window.showErrorMessage(
            "No InfiniteScript file is open."
        );
        return null;
    }

    if (editor.document.languageId !== "infinite-script") {
        vscode.window.showErrorMessage(
            "The current file is not an InfiniteScript file."
        );
        return null;
    }

    return editor.document.uri.fsPath;
}

function quoteArgument(value) {
    return `"${String(value).replace(/"/g, '\\"')}"`;
}

function runTerminal(args, terminalName) {

    const workspaceRoot = getWorkspaceRoot();

    if (!workspaceRoot) {
        vscode.window.showErrorMessage(
            "Open your InfiniteScript project folder first."
        );
        return;
    }

    const executable = findInfiniteScript(workspaceRoot);

    if (!executable) {
        vscode.window.showErrorMessage(
            "Could not find Inf.exe."
        );
        return;
    }

    const terminal = vscode.window.createTerminal({
        name: terminalName,
        cwd: workspaceRoot
    });

    terminal.show();

    terminal.sendText(
        `${quoteArgument(executable)} ${args.join(" ")}`
    );
}

/* =========================================================
   Run
   ========================================================= */

function runCurrentFile() {

    const file = getCurrentFile();

    if (!file) {
        return;
    }

    runTerminal(
        ["run", quoteArgument(file)],
        "InfiniteScript ▶ Run"
    );
}

/* =========================================================
   Check
   ========================================================= */

function checkCurrentFile() {

    const file = getCurrentFile();

    if (!file) {
        return;
    }

    const workspaceRoot = getWorkspaceRoot();

    if (!workspaceRoot) {
        return;
    }

    const executable = findInfiniteScript(workspaceRoot);

    if (!executable) {
        vscode.window.showErrorMessage(
            "Could not find Inf.exe."
        );
        return;
    }

    diagnosticCollection.clear();

    cp.execFile(
        executable,
        ["check", file],
        {
            cwd: workspaceRoot,
            windowsHide: true
        },
        (error, stdout, stderr) => {

            const output =
                `${stdout}\n${stderr}`;

            const diagnostics =
                parseDiagnostics(output);

            diagnosticCollection.set(
                vscode.Uri.file(file),
                diagnostics
            );

            if (diagnostics.length === 0) {

                if (error) {
                    vscode.window.showErrorMessage(
                        output.trim() ||
                        "InfiniteScript check failed."
                    );
                } else {
                    vscode.window.showInformationMessage(
                        "✓ InfiniteScript check passed."
                    );
                }

            } else {

                vscode.window.showErrorMessage(
                    `InfiniteScript found ${diagnostics.length} error(s).`
                );
            }
        }
    );
}

/* =========================================================
   Diagnostics
   ========================================================= */

function parseDiagnostics(output) {

    const diagnostics = [];
    const lines = output.split(/\r?\n/);

    let current = null;

    for (const line of lines) {

        const errorMatch =
            line.match(/Error\s+\[(INF\d+)\]/);

        if (errorMatch) {

            current = {
                code: errorMatch[1],
                line: 0
            };

            continue;
        }

        if (!current) {
            continue;
        }

        const lineMatch =
            line.match(/Line:\s*(\d+)/);

        if (lineMatch) {

            current.line =
                Math.max(
                    0,
                    Number(lineMatch[1]) - 1
                );

            continue;
        }

        if (
            line.trim() &&
            !line.startsWith("-") &&
            !line.startsWith("File:")
        ) {

            diagnostics.push(
                new vscode.Diagnostic(
                    new vscode.Range(
                        current.line,
                        0,
                        current.line,
                        Number.MAX_SAFE_INTEGER
                    ),
                    `${line.trim()} [${current.code}]`,
                    vscode.DiagnosticSeverity.Error
                )
            );

            current = null;
        }
    }

    return diagnostics;
}

/* =========================================================
   Build
   ========================================================= */

function buildProject() {

    runTerminal(
        ["build"],
        "InfiniteScript 🔨 Build"
    );
}

/* =========================================================
   Parse current InfiniteScript
   ========================================================= */

function parseSymbols(document) {

    const text = document.getText();

    const variables = new Map();
    const functions = new Map();

    const lines = text.split(/\r?\n/);

    for (let i = 0; i < lines.length; i++) {

        const line = lines[i].trim();

        /*
         * Local Storage
         */
        let match =
            line.match(
                /^Local Storage\s+([A-Za-z_][A-Za-z0-9_]*)/
            );

        if (match) {

            variables.set(
                match[1],
                {
                    kind: "Local Storage",
                    line: i
                }
            );

            continue;
        }

        /*
         * Set
         */
        match =
            line.match(
                /^Set\s+([A-Za-z_][A-Za-z0-9_]*)/
            );

        if (match) {

            variables.set(
                match[1],
                {
                    kind: "Variable",
                    line: i
                }
            );

            continue;
        }

        /*
         * Input
         */
        match =
            line.match(
                /^Input(?:\s+(?:Number|Boolean))?\s+([A-Za-z_][A-Za-z0-9_]*)/
            );

        if (match) {

            variables.set(
                match[1],
                {
                    kind: "Input",
                    line: i
                }
            );

            continue;
        }

        /*
         * Random
         */
        match =
            line.match(
                /^Random\s+Number\s+([A-Za-z_][A-Za-z0-9_]*)/
            );

        if (match) {

            variables.set(
                match[1],
                {
                    kind: "Random Number",
                    line: i
                }
            );

            continue;
        }

        /*
         * Function
         */
        match =
            line.match(
                /^(?:Local\s+)?Function\s+([A-Za-z_][A-Za-z0-9_]*)(.*)$/
            );

        if (match) {

            const name = match[1];

            const parameters =
                match[2]
                    .trim()
                    .split(/\s+/)
                    .filter(Boolean);

            functions.set(
                name,
                {
                    parameters,
                    line: i
                }
            );
        }
    }

    return {
        variables,
        functions
    };
}

/* =========================================================
   IntelliSense
   ========================================================= */

function provideCompletions(document) {

    const symbols =
        parseSymbols(document);

    const items = [];

    /*
     * Language commands
     */

    for (const keyword of keywords) {

        const item =
            new vscode.CompletionItem(
                keyword,
                vscode.CompletionItemKind.Keyword
            );

        item.detail =
            "InfiniteScript command";

        item.documentation =
            new vscode.MarkdownString(
                documentation[keyword] ||
                `InfiniteScript command: **${keyword}**`
            );

        items.push(item);
    }

    /*
     * Variables
     */

    for (const [name, info] of symbols.variables) {

        const item =
            new vscode.CompletionItem(
                name,
                vscode.CompletionItemKind.Variable
            );

        item.detail =
            info.kind;

        item.documentation =
            new vscode.MarkdownString(
                `InfiniteScript ${info.kind.toLowerCase()} **${name}**`
            );

        items.push(item);
    }

    /*
     * Functions
     */

    for (const [name, info] of symbols.functions) {

        const item =
            new vscode.CompletionItem(
                name,
                vscode.CompletionItemKind.Function
            );

        item.detail =
            "InfiniteScript function";

        item.insertText =
            new vscode.SnippetString(
                info.parameters.length
                    ? `${name} ${info.parameters.map((_, i) => `\${${i + 1}}`).join(" ")}`
                    : name
            );

        item.documentation =
            new vscode.MarkdownString(
                `InfiniteScript function **${name}**`
            );

        items.push(item);
    }

    return items;
}

/* =========================================================
   Hover
   ========================================================= */

function provideHover(document, position) {

    const range =
        document.getWordRangeAtPosition(
            position,
            /[A-Za-z_][A-Za-z0-9_]*/
        );

    if (!range) {
        return null;
    }

    const word =
        document.getText(range);

    if (documentation[word]) {

        return new vscode.Hover(
            new vscode.MarkdownString(
                `### ${word}\n\n${documentation[word]}`
            )
        );
    }

    const symbols =
        parseSymbols(document);

    if (symbols.variables.has(word)) {

        const info =
            symbols.variables.get(word);

        return new vscode.Hover(
            new vscode.MarkdownString(
                `### ${word}\n\n**${info.kind}**`
            )
        );
    }

    if (symbols.functions.has(word)) {

        const info =
            symbols.functions.get(word);

        const params =
            info.parameters.length
                ? ` ${info.parameters.join(" ")}`
                : "";

        return new vscode.Hover(
            new vscode.MarkdownString(
                `### ${word}\n\nFunction: \`${word}${params}\``
            )
        );
    }

    return null;
}

/* =========================================================
   Status bar
   ========================================================= */

function createStatusBar(context) {

    const item =
        vscode.window.createStatusBarItem(
            vscode.StatusBarAlignment.Left,
            100
        );

    item.text =
        "$(play) InfiniteScript";

    item.tooltip =
        "Run current InfiniteScript file";

    item.command =
        "infiniteScript.run";

    item.show();

    context.subscriptions.push(item);
}

/* =========================================================
   Activate
   ========================================================= */

function activate(context) {

    diagnosticCollection =
        vscode.languages.createDiagnosticCollection(
            "infinite-script"
        );

    context.subscriptions.push(
        diagnosticCollection
    );

    context.subscriptions.push(
        vscode.commands.registerCommand(
            "infiniteScript.run",
            runCurrentFile
        )
    );

    context.subscriptions.push(
        vscode.commands.registerCommand(
            "infiniteScript.check",
            checkCurrentFile
        )
    );

    context.subscriptions.push(
        vscode.commands.registerCommand(
            "infiniteScript.build",
            buildProject
        )
    );

    context.subscriptions.push(
        vscode.languages.registerCompletionItemProvider(
            "infinite-script",
            {
                provideCompletionItems
            }
        )
    );

    context.subscriptions.push(
        vscode.languages.registerHoverProvider(
            "infinite-script",
            {
                provideHover
            }
        )
    );

    createStatusBar(context);

    vscode.window.setStatusBarMessage(
        "InfiniteScript activated ✓",
        3000
    );
}

function deactivate() {
    if (diagnosticCollection) {
        diagnosticCollection.dispose();
    }
}

module.exports = {
    activate,
    deactivate
};
