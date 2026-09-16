document.addEventListener("DOMContentLoaded", () => {

    const cards = document.querySelectorAll(".feature-card");

    const observer = new IntersectionObserver(
        entries => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    entry.target.style.opacity = "1";
                    entry.target.style.transform = "translateY(0)";
                }
            });
        },
        {
            threshold: 0.12
        }
    );

    cards.forEach(card => {
        card.style.opacity = "0";
        card.style.transform = "translateY(18px)";
        card.style.transition =
            "opacity .6s ease, transform .6s ease, border-color .25s";

        observer.observe(card);
    });


    // Smooth scrolling for internal links

    document.querySelectorAll('a[href^="#"]').forEach(link => {

        link.addEventListener("click", event => {

            const target = document.querySelector(
                link.getAttribute("href")
            );

            if (!target) return;

            event.preventDefault();

            target.scrollIntoView({
                behavior: "smooth",
                block: "start"
            });

        });

    });

});
