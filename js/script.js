/* ========================================
   FETCH GITHUB COMMIT DATES
   ========================================
   Dynamically updates the "Updated" timestamps on project cards
   Uses GitHub API to get the latest commit date for each repository
   Formats the date as "Updated X days ago" or "Updated today"
   ======================================== */

async function updateCommitDates() {
    // Get all elements with data-repo attribute
    const updatedElements = document.querySelectorAll('[data-repo]');
    
    updatedElements.forEach(async (element) => {
        const repo = element.getAttribute('data-repo');
        
        try {
            // Fetch latest commit from GitHub API
            // Using the public API (no auth token required for public repos)
            const response = await fetch(`https://api.github.com/repos/${repo}/commits?per_page=1`);
            
            if (!response.ok) {
                throw new Error(`GitHub API error: ${response.status}`);
            }
            
            const commits = await response.json();
            
            // Check if we got commit data
            if (commits.length > 0) {
                const lastCommitDate = new Date(commits[0].commit.author.date);
                const formattedDate = formatDateRelative(lastCommitDate);
                element.textContent = `Updated ${formattedDate}`;
            } else {
                // Fallback if no commits found
                element.textContent = 'No commits found';
            }
        } catch (error) {
            // Log error but keep original text visible
            console.error(`Error fetching commit data for ${repo}:`, error);
            element.textContent = 'Unable to fetch update date';
        }
    });
}

/* ========================================
   FORMAT DATE AS RELATIVE TIME
   ========================================
   Converts a Date object to human-readable relative time
   Examples: "today", "2 days ago", "3 weeks ago", "6 months ago"
   ======================================== */

function formatDateRelative(date) {
    const now = new Date();
    const diffMs = now - date;
    const diffDays = Math.floor(diffMs / (1000 * 60 * 60 * 24));
    const diffWeeks = Math.floor(diffDays / 7);
    const diffMonths = Math.floor(diffDays / 30);
    const diffYears = Math.floor(diffDays / 365);
    
    // Choose the most appropriate time unit
    if (diffDays === 0) {
        return 'today';
    } else if (diffDays === 1) {
        return 'yesterday';
    } else if (diffDays < 7) {
        return `${diffDays} days ago`;
    } else if (diffWeeks < 4) {
        return `${diffWeeks} week${diffWeeks > 1 ? 's' : ''} ago`;
    } else if (diffMonths < 12) {
        return `${diffMonths} month${diffMonths > 1 ? 's' : ''} ago`;
    } else {
        return `${diffYears} year${diffYears > 1 ? 's' : ''} ago`;
    }
}

// Call the function when page loads
document.addEventListener('DOMContentLoaded', updateCommitDates);

/* ========================================
   SMOOTH SCROLL BEHAVIOR
   ========================================
   Enables smooth scrolling for anchor links
   ======================================== */

document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
            target.scrollIntoView({
                behavior: 'smooth'
            });
        }
    });
});

/* ========================================
   SCROLL ANIMATION FOR PROJECT CARDS
   ========================================
   Observes when project cards enter the viewport
   Animates them in with fade + slide up effect
   Uses Intersection Observer API for performance
   ======================================== */

// Animation trigger when cards become visible
const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -100px 0px'
};

const observer = new IntersectionObserver(function(entries) {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.style.opacity = '1';
            entry.target.style.transform = 'translateY(0)';
        }
    });
}, observerOptions);

// Initialize cards as invisible, then observe them
document.querySelectorAll('.project-card').forEach(card => {
    card.style.opacity = '0';
    card.style.transform = 'translateY(20px)';
    card.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
    observer.observe(card);
});
