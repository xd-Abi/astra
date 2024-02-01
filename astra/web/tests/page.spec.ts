import { test, expect } from '@playwright/test';

test('redirecting to Google after searching', async ({ page }) => {
  await page.goto('http://localhost:4000/', { waitUntil: 'networkidle' });

  const searchInputSelector = 'input';
  await page.fill(searchInputSelector, 'marwin');
  await page.press(searchInputSelector, 'Enter');
  await page.waitForLoadState('networkidle');

  const expectedURL = 'https://www.google.com/search?q=marwin';
  await expect(page).toHaveURL(expectedURL);
});
