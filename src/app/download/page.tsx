export default function Home() {
  return (
    <main className="w-full min-h-screen bg-[#0a071b] flex items-center justify-center">
      <div className="text-center">
        <h1 className="uppercase font-light text-md text-[#61cce9]">
          TAKE BROWSERING TO NEXT LEVEL
        </h1>
        <p className="pt-3 font-bold text-white text-7xl">Turn your ideas</p>
        <p className="pt-3 font-bold text-white text-7xl">into reality.</p>
        <p className="pt-10 font-normal text-slate-400 text-xs">
          Everything you need to build your landing page and
        </p>
        <p className="pt-2 font-normal text-slate-400 text-xs">
          make a great impression.
        </p>

        <div className="pt-10 flex gap-3 justify-center">
          <a
            href="/Test.zip"
            className="px-6 py-2 rounded-full bg-[#5138ee] border-2 border-[#5138ee] text-white font-medium hover:bg-transparent transition-all duration-200 ease-in"
          >
            Download
          </a>
          <a
            href="/Test.zip"
            className="px-6 py-2 rounded-full bg-transparent border-2 border-[#5138ee] text-white font-medium hover:bg-[#5138ee] transition-all duration-200 ease-in"
          >
            Contact us
          </a>
        </div>
      </div>
    </main>
  );
}
