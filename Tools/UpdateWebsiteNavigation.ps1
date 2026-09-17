$files = Get-ChildItem ".\docs" -Filter "*.html"

$nav = @'
<nav class="site-nav">
    <a href="index.html" class="site-brand">
        <span class="site-logo">∞</span>
        <span>InfiniteScript</span>
    </a>

    <div class="site-links">
        <a href="index.html">Home</a>
        <a href="documentation.html">Docs</a>
        <a href="tutorial.html">Tutorial</a>
        <a href="examples.html">Examples</a>
        <a href="dictionary.html">Dictionary</a>
        <a href="playground.html">Playground</a>
        <a href="cli.html">CLI</a>
        <a href="downloads.html">Download</a>
        <a href="changelog.html">Changelog</a>
        <a href="errors.html">Errors</a>
        <a href="roadmap.html">Roadmap</a>
        <a href="https://github.com/gameworldyt/Infinite-Script" target="_blank" rel="noopener">
            GitHub
        </a>
    </div>
</nav>
'@

$css = @'
<style id="infinite-nav-style">
.site-nav {
    position: sticky;
    top: 0;
    z-index: 9999;

    min-height: 72px;

    display: flex;
    align-items: center;
    justify-content: space-between;

    gap: 30px;
    padding: 12px 6%;

    background:
        linear-gradient(
            90deg,
            rgba(2, 6, 13, .96),
            rgba(5, 20, 35, .92)
        );

    border-bottom: 1px solid rgba(103, 232, 249, .16);

    backdrop-filter: blur(18px);
    -webkit-backdrop-filter: blur(18px);
}

.site-brand {
    display: flex;
    align-items: center;
    gap: 10px;

    flex-shrink: 0;

    color: #e8f8ff;
    text-decoration: none;

    font-size: 18px;
    font-weight: 800;
    letter-spacing: -.5px;
}

.site-logo {
    width: 38px;
    height: 38px;

    display: grid;
    place-items: center;

    border-radius: 11px;

    color: white;
    font-size: 25px;

    background:
        linear-gradient(
            135deg,
            #075985,
            #22d3ee
        );

    box-shadow:
        0 0 25px rgba(34, 211, 238, .35);

    transition:
        transform .25s ease,
        box-shadow .25s ease;
}

.site-brand:hover .site-logo {
    transform: rotate(-8deg) scale(1.08);

    box-shadow:
        0 0 35px rgba(34, 211, 238, .65);
}

.site-links {
    display: flex;
    align-items: center;
    justify-content: flex-end;

    gap: 15px;
    flex-wrap: wrap;

    font-size: 12px;
}

.site-links a {
    position: relative;

    color: #8ba6b8;
    text-decoration: none;

    transition:
        color .2s ease,
        transform .2s ease;
}

.site-links a::after {
    content: "";

    position: absolute;
    left: 0;
    bottom: -6px;

    width: 0;
    height: 2px;

    border-radius: 999px;

    background: #67e8f9;

    transition: width .2s ease;
}

.site-links a:hover {
    color: #67e8f9;
    transform: translateY(-1px);
}

.site-links a:hover::after {
    width: 100%;
}

@media (max-width: 1200px) {
    .site-links {
        gap: 11px;
    }

    .site-links a:nth-child(n+9) {
        display: none;
    }
}

@media (max-width: 760px) {
    .site-nav {
        align-items: flex-start;
        flex-direction: column;
        gap: 14px;
    }

    .site-links {
        width: 100%;
        justify-content: flex-start;
        gap: 12px;
    }

    .site-links a {
        display: inline-block !important;
    }
}
</style>
'@

foreach ($file in $files) {
    Write-Host "Updating $($file.Name)..."

    $html = Get-Content $file.FullName -Raw

    # Remove previously generated navigation.
    $html = [regex]::Replace(
        $html,
        '(?is)<nav class="site-nav">.*?</nav>',
        ''
    )

    # Remove previously generated navigation CSS.
    $html = [regex]::Replace(
        $html,
        '(?is)<style id="infinite-nav-style">.*?</style>',
        ''
    )

    # Insert navigation after <body>.
    if ($html -match '(?i)<body[^>]*>') {
        $html = [regex]::Replace(
            $html,
            '(?i)<body[^>]*>',
            {
                param($match)

                $match.Value + "
" + $nav
            },
            1
        )
    }

    # Insert CSS before </head>.
    if ($html -match '(?i)</head>') {
        $html = $html -replace '(?i)</head>', ($css + "
</head>")
    }

    Set-Content 
        -Path $file.FullName 
        -Value $html 
        -Encoding UTF8
}

Write-Host ""
Write-Host "=============================================="
Write-Host " InfiniteScript navigation updated successfully"
Write-Host "=============================================="
Write-Host ""

Get-ChildItem ".\docs" -Filter "*.html" |
    Select-Object Name, Length
