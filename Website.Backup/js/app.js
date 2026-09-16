document.addEventListener("DOMContentLoaded", () => {
    const elements = document.querySelectorAll(
        ".card, .feature-card, .section, .code-window, .docs-content > *"
    );

    elements.forEach(element => {
        element.classList.add("reveal");
    });

    const observer = new IntersectionObserver(
        entries => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    entry.target.classList.add("visible");
                    observer.unobserve(entry.target);
                }
            });
        },
        {
            threshold: 0.12
        }
    );

    document.querySelectorAll(".reveal").forEach(element => {
        observer.observe(element);
    });

    document.querySelectorAll("a[href]").forEach(link => {
        const href = link.getAttribute("href");

        if (
            href &&
            href.startsWith("#") &&
            href.length > 1
        ) {
            link.addEventListener("click", event => {
                const target = document.querySelector(href);

                if (target) {
                    event.preventDefault();
                    target.scrollIntoView({
                        behavior: "smooth",
                        block: "start"
                    });
                }
            });
        }
    });

    document.querySelectorAll("[data-copy]").forEach(button => {
        button.addEventListener("click", async () => {
            const text = button.getAttribute("data-copy");

            try {
                await navigator.clipboard.writeText(text);
                const oldText = button.textContent;
                button.textContent = "Copied!";
                setTimeout(() => {
                    button.textContent = oldText;
                }, 1400);
            } catch {
                button.textContent = "Copy failed";
            }
        });
    });
});
