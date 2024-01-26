import { Metadata } from 'next';

export const metadata: Metadata = {
  title: 'Download - Astra'
};

export default function DownloadPage() {
  return (
    <main className="w-full min-h-screen bg-black overflow-x-hidden flex items-center justify-center">
      <div className="text-center pb-60">
        <p className="font-sans font-normal text-2xl text-blue-200">TAKE BROWSERING TO NEXT LEVEL</p>
        <div className="bg-clip-text bg-gradient-to-b from-blue-300 to-blue-500">
          <p className="pt-5 font-sans font-bold text-9xl text-transparent">Turn your ideas</p>
          <p className="pt-3 font-sans font-bold text-9xl text-transparent">into reality.</p>
        </div>
        <p className="pt-12 text-slate-400">
          Unleash the Power of Play with Our{' '}
          <strong className="bg-clip-text bg-gradient-to-b from-blue-300 to-blue-500 text-transparent">
            Cutting-Edge Browser
          </strong>{' '}
          - Where Gaming
        </p>
        <p className="pt-2 pb-10 text-slate-400">
          Dreams Come to Life in a Single{' '}
          <strong className="bg-clip-text bg-gradient-to-b from-blue-300 to-blue-500 text-transparent">Click</strong>!
        </p>
        <div className="w-full flex justify-center">
          <a
            href="./astra-installer-template.zip"
            className="rounded-full w-fit px-10 py-4 flex gap-2 items-center text-lg font-bold text-white bg-gradient-to-br from-blue-300 to-blue-500 hover:scale-105 transition-all duration-200 ease-in"
          >
            <svg
              xmlns="http://www.w3.org/2000/svg"
              fill="none"
              viewBox="0 0 24 24"
              strokeWidth="2"
              stroke="currentColor"
              className="w-6 h-6"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                d="m9 12.75 3 3m0 0 3-3m-3 3v-7.5M21 12a9 9 0 1 1-18 0 9 9 0 0 1 18 0Z"
              />
            </svg>
            Download
          </a>
        </div>
      </div>
    </main>
  );
}
